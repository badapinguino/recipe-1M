#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <iostream> //DA RIMUOVERE, usato per i cout
#include <QImageReader>
#include <QListWidgetItem>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupIniziale();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupIniziale(){
    ui->stackedWidget->setStyleSheet("background-color: lightGrey;");
    ui->stackedWidget->setCurrentIndex(0);
    //main page
    ui->RecipeSearchButton->setStyleSheet("background-color: #008040;font-size: 16px;height: 48px;width: 120px;");
    ui->IngredientSearchButton->setStyleSheet("background-color: #008040;font-size: 16px;height: 48px;width: 120px;");
    ui->StatisticsButton->setStyleSheet("background-color: #008040;font-size: 16px;height: 48px;width: 120px;");
    ui->labelTitle->setStyleSheet("font-size: 25px; color: #008080; height: 40px;");
    //recipe search page
    ui->HomeButtonInRecipePage->setStyleSheet("background-color: #008040;font-size: 16px");
    ui->SearchButtonInRecipePage->setStyleSheet("background-color: #cccc00;");
    ui->LineEditSearchRecipe->setStyleSheet("background-color: #fefefe;");
    ui->ListWidgetIngredients->setStyleSheet("background-color: #eeeeee;");
    ui->ListWidgetInstructions->setStyleSheet("background-color: #eeeeee;");
    ui->ListWidgetMatchingResult->setStyleSheet("background-color: #eeeeee;");
    //ingredient search page
    ui->HomeButtonInIngredientPage->setStyleSheet("background-color: #008040;font-size: 16px");
    ui->SearchButtonInIngredientPage->setStyleSheet("background-color: #cccc00;");
    ui->LineEditSearchIngredient->setStyleSheet("background-color: #fefefe;");
    ui->ListWidgetStandardIngredients->setStyleSheet("background-color: #eeeeee;");
    ui->ListWidgetRecipesContainingIngredient->setStyleSheet("background-color: #eeeeee;");
    //statistics page
    ui->HomeButtonInStatisticsPage->setStyleSheet("background-color: #008040;font-size: 16px");
    ui->SearchButtonInStatisticsPage->setStyleSheet("background-color: #cccc00;");
    ui->LineEditSearchNumberRecipesForIngredients->setStyleSheet("background-color: #fefefe;");
    ui->NumberRecipesForStdIngredientTable->setStyleSheet("background-color: #eeeeee;");
    statisticsPageAlreadyVisited=false;

    setCentralWidget(ui->stackedWidget);

    //controllo connessione al DB
    bool ok = db.connectionOk();
    if(!ok){
        QMessageBox::critical(
          this,
          tr("Database connection error!"),
          tr("Unable to connect to database, check your connection or your database status and retry.") );
        delete ui;
        std::exit(0);
    }
}


/* METODI PER RECIPE PAGE */

void MainWindow::searchButtonInRecipePagePressed(){
    //pulisce gli altri elementi della pagina
    ui->ListWidgetMatchingResult->clear();
    ui->ListWidgetIngredients->clear();
    ui->ListWidgetInstructions->clear();
    ui->ImageLabel->clear();
    //visualizzare una scritta di attesa
    QCoreApplication::processEvents();
    ui->ListWidgetMatchingResult->addItem("Loading result, please wait...");
    // let the application process its events
    QCoreApplication::processEvents();
    //catturo il testo da cercare inserito dall'utente
    QString testoDaCercare = ui->LineEditSearchRecipe->text();
    // nel caso il testo da cercare sia vuoto chiedo conferma all'utente tramite una finestra di alert che voglia cercare in tutto il db dato che ci impiegherà molto tempo
    bool testoDaCercareSure = true;
    if(testoDaCercare.length()==0 || testoDaCercare.toStdString()==""){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Are you sure?", "Are you sure to search all the recipes in the database? It can requires even one or more minutes!", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            testoDaCercareSure = true;
        } else {
            testoDaCercareSure = false;
        }
    }
    //apertura connessione al db e query
    bool ok = db.connectionOk();
    if(ok==true){
        if(testoDaCercareSure==true){
            QSqlQuery richiesta;
            //esegue la query
            richiesta = db.executeQuery("select distinct title from Recipe where title like '%" + testoDaCercare.replace("\"","\\\"").replace("\'","\\\'") + "%' order by title asc;");
            QStringList items;
            QString firstItem;
            // pulisce la lista da eventuali altre ricerche precedenti
            listaUrlImmagini.clear();
            // cicla sui risultati e li inserisce nella UI
            if(richiesta.size()!=0){
                for(int i=0; richiesta.next(); i++) {
                    QString name = richiesta.value(0).toString();
                    if(i==0){
                        firstItem = name;
                    }
                    items+=name;
                }
                ui->ListWidgetMatchingResult->clear();
                ui->ListWidgetMatchingResult->addItems(items);
                //trovo l'id della prima ricetta visualizzata
                QSqlQuery richiestaIdFirstItem;
                QString idFirst;
                richiestaIdFirstItem = db.executeQuery("select id from Recipe where title='" + firstItem.replace("\"","\\\"").replace("\'","\\\'") + "' limit 1;");
                for(int i=0; richiestaIdFirstItem.next(); i++) {
                    idFirst = richiestaIdFirstItem.value(0).toString();
                }
                //cerco gli ingredienti con quantità relativi alla ricetta con id trovato
                QSqlQuery richiestaIngredientsIdRecipe;
                richiestaIngredientsIdRecipe = db.executeQuery("select description from Ingredient where id_recipe='" + idFirst + "';");
                for(int i=0; richiestaIngredientsIdRecipe.next(); i++) {
                    QString ingredient = richiestaIngredientsIdRecipe.value(0).toString();
                    ui->ListWidgetIngredients->addItem(ingredient);
                }
                //cerco le istruzioni della ricetta con id trovato
                QSqlQuery richiestaInstructionsIdRecipe;
                richiestaInstructionsIdRecipe = db.executeQuery("select description from Instruction where id_recipe='" + idFirst + "';");
                for(int i=0; richiestaInstructionsIdRecipe.next(); i++) {
                    QString instruction = richiestaInstructionsIdRecipe.value(0).toString();
                    ui->ListWidgetInstructions->addItem("• "+instruction);
                }
                //cerco la prima immagine della ricetta con id trovato
                QSqlQuery richiestaImagesIdRecipe;
                richiestaImagesIdRecipe = db.executeQuery("select url from Image where id_recipe='" + idFirst + "';");
                QString image;
                QImage img;
                try{
                    QNetworkAccessManager *nam = new QNetworkAccessManager(this);
                    urlImmagineVisualizzata="";
                    ui->ImageLabel->setText("No image found");
                    // scarico la foto dall'url indicato attraverso il processo seguente
                    for(int i=0; richiestaImagesIdRecipe.next(); i++) {
                        image = richiestaImagesIdRecipe.value(0).toString();
                        listaUrlImmagini += image;
                        ui->ImageLabel->setScaledContents(true);
                        QUrl url(image);
                        QNetworkReply* reply = nam->get(QNetworkRequest(url));
                        QEventLoop eventLoop;
                        connect(reply,SIGNAL(finished()),&eventLoop,SLOT(quit()));
                        eventLoop.exec();
                        // inserisco l'immagine scaricata nella label
                        if (reply->error() == QNetworkReply::NoError){
                            QImageReader imageReader(reply);
                            img = imageReader.read();
                            urlImmagineVisualizzata=image;
                            ui->ImageLabel->setPixmap(QPixmap::fromImage(img));
                        }else{
                            ui->ImageLabel->setText("Impossibile to estabilish a connection");
                        }
                    }
                    delete nam;
                }catch(...){
                    QMessageBox::critical(
                      this,
                      tr("Network connection error!"),
                      tr("Unable to connect to the internet, check your connection and retry.") );
                }
            }else{
                ui->ListWidgetMatchingResult->clear();
                ui->ListWidgetMatchingResult->addItem("No recipe found");
            }
        }else{
            ui->ListWidgetMatchingResult->clear();
        }
    }else{
        QMessageBox::critical(
          this,
          tr("Database connection error!"),
          tr("Unable to connect to database, check your connection or your database status and retry.") );
        delete ui;
        std::exit(0);
    }
}


void MainWindow::RecipeSelectedFromList(QString nomeRicettaSelezionata){
    //pulisce gli altri elementi della pagina
    ui->ListWidgetIngredients->clear();
    ui->ListWidgetInstructions->clear();
    ui->ImageLabel->clear();
    listaUrlImmagini.clear();
    //apertura connessione al db e query
    bool ok = db.connectionOk();
    if(ok==true){
        //trovo l'id della ricetta selezionata
        QSqlQuery richiestaIdFirstItem;
        QString idSelezionato;
        richiestaIdFirstItem = db.executeQuery("select id from Recipe where title='" + nomeRicettaSelezionata.replace("\"","\\\"").replace("\'","\\\'") + "' limit 1;");
        for(int i=0; richiestaIdFirstItem.next(); i++) {
            idSelezionato = richiestaIdFirstItem.value(0).toString();
        }
        //cerco gli ingredienti con quantità relativi alla ricetta con id trovato
        QSqlQuery richiestaIngredientsIdRecipe;
        richiestaIngredientsIdRecipe = db.executeQuery("select description from Ingredient where id_recipe='" + idSelezionato + "';");
        for(int i=0; richiestaIngredientsIdRecipe.next(); i++) {
            QString ingredient = richiestaIngredientsIdRecipe.value(0).toString();
            ui->ListWidgetIngredients->addItem(ingredient);
        }
        //cerco le istruzioni della ricetta con id trovato
        QSqlQuery richiestaInstructionsIdRecipe;
        richiestaInstructionsIdRecipe = db.executeQuery("select description from Instruction where id_recipe='" + idSelezionato + "';");
        for(int i=0; richiestaInstructionsIdRecipe.next(); i++) {
            QString instruction = richiestaInstructionsIdRecipe.value(0).toString();
            ui->ListWidgetInstructions->addItem("• "+instruction);
        }
        //cerco la prima immagine della ricetta con id trovato
        QSqlQuery richiestaImagesIdRecipe;
        richiestaImagesIdRecipe = db.executeQuery("select url from Image where id_recipe='" + idSelezionato + "';");
        QString image;
        QImage img;
        try{
            QNetworkAccessManager *nam = new QNetworkAccessManager(this);
            urlImmagineVisualizzata="";
            ui->ImageLabel->setText("No image found");
            // scarico la foto dall'url indicato attraverso il processo seguente
            for(int i=0; richiestaImagesIdRecipe.next(); i++) {
                image = richiestaImagesIdRecipe.value(0).toString();
                listaUrlImmagini += image;
                ui->ImageLabel->setScaledContents(true);
                QUrl url(image);
                QNetworkReply* reply = nam->get(QNetworkRequest(url));
                QEventLoop eventLoop;
                connect(reply,SIGNAL(finished()),&eventLoop,SLOT(quit()));
                eventLoop.exec();
                // inserisco la foto scaricata nella label
                if (reply->error() == QNetworkReply::NoError){
                    QImageReader imageReader(reply);
                    img = imageReader.read();
                    urlImmagineVisualizzata=image;
                    ui->ImageLabel->setPixmap(QPixmap::fromImage(img));
                }else{
                    ui->ImageLabel->setText("Impossibile to estabilish a connection");
                }
            }
            delete nam;
        }catch(...){
        QMessageBox::critical(
          this,
          tr("Network connection error!"),
          tr("Unable to connect to the internet, check your connection and retry.") );
        }
    }else{
        QMessageBox::critical(
            this,
            tr("Database connection error!"),
            tr("Unable to connect to database, check your connection or your database status and retry.") );
        delete ui;
        std::exit(0);
    }
}


void MainWindow::loadNextImage(){
    //calcolo posizione immagine visualizzata
    int posizione=-1;
    for(int i=0;i<listaUrlImmagini.length();i++){
        if(urlImmagineVisualizzata==listaUrlImmagini[i]){
            posizione=i;
        }
    }
    QImage img;
    try{
        QNetworkAccessManager *nam = new QNetworkAccessManager(this);
        QString image;
        if(posizione!=-1){
            if(posizione<listaUrlImmagini.length()-1){
                image = listaUrlImmagini[posizione+1];
            }else{
                image = listaUrlImmagini[0];
            }
            ui->ImageLabel->setScaledContents(true);
            QUrl url(image);
            QNetworkReply* reply = nam->get(QNetworkRequest(url));
            QEventLoop eventLoop;
            connect(reply,SIGNAL(finished()),&eventLoop,SLOT(quit()));
            eventLoop.exec();
            if (reply->error() == QNetworkReply::NoError)
            {
                QImageReader imageReader(reply);
                img = imageReader.read();
                urlImmagineVisualizzata=image;
            }
            ui->ImageLabel->setPixmap(QPixmap::fromImage(img));
        }else{
            ui->ImageLabel->setText("");
        }
        delete nam;
    }catch(...){
        QMessageBox::critical(
          this,
          tr("Network connection error!"),
          tr("Unable to connect to the internet, check your connection and retry.") );
    }
}

void MainWindow::loadPreviousImage(){
    //calcolo posizione immagine visualizzata
    int posizione=-1;
    for(int i=0;i<listaUrlImmagini.length();i++){
        if(urlImmagineVisualizzata==listaUrlImmagini[i]){
            posizione=i;
        }
    }
    QImage img;
    try{
        QNetworkAccessManager *nam = new QNetworkAccessManager(this);
        QString image;
        if(posizione!=-1){
            QString image;
            if(posizione>0){
                image = listaUrlImmagini[posizione-1];
            }else{
                image = listaUrlImmagini[listaUrlImmagini.length()-1];
            }
            ui->ImageLabel->setScaledContents(true);
            QUrl url(image);
            QNetworkReply* reply = nam->get(QNetworkRequest(url));
            QEventLoop eventLoop;
            connect(reply,SIGNAL(finished()),&eventLoop,SLOT(quit()));
            eventLoop.exec();
            if (reply->error() == QNetworkReply::NoError)
            {
                QImageReader imageReader(reply);
                img = imageReader.read();
                urlImmagineVisualizzata=image;
            }
            ui->ImageLabel->setPixmap(QPixmap::fromImage(img));
        }else{
            ui->ImageLabel->setText("");
        }
        delete nam;
    }catch(...){
        QMessageBox::critical(
          this,
          tr("Network connection error!"),
          tr("Unable to connect to the internet, check your connection and retry.") );
    }
}

/* METODI PER INGREDIENT PAGE */

void MainWindow::searchButtonInIngredientPagePressed(){
    //pulisce gli altri elementi della pagina
    ui->LabelNumberRecipes->setText("Total numbers of recipes containing the ingredient: ");
    ui->ListWidgetStandardIngredients->clear();
    ui->ListWidgetRecipesContainingIngredient->clear();
    QCoreApplication::processEvents();
    ui->ListWidgetStandardIngredients->addItem("Loading result, please wait...");
    // let the application process its events
    QCoreApplication::processEvents();
    QString testoDaCercare = ui->LineEditSearchIngredient->text();
    bool testoDaCercareSure = true;
    // nel caso il testo da cercare sia vuoto chiedo conferma all'utente tramite una finestra di alert che voglia cercare in tutto il db dato che ci impiegherà molto tempo
    if(testoDaCercare.length()==0 || testoDaCercare.toStdString()==""){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Are you sure?", "Are you sure to search all the ingredients in the database?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            testoDaCercareSure = true;
        } else {
            testoDaCercareSure = false;
        }
    }
    //apertura connessione al db e query
    bool ok = db.connectionOk();
    if(ok==true){
        if(testoDaCercareSure==true){
            QSqlQuery richiesta;
            richiesta = db.executeQuery("select distinct name_ingredient from Standard_Ingredient where valid=true and name_ingredient like '%" + testoDaCercare.replace("\"","\\\"").replace("\'","\\\'") + "%' order by name_ingredient asc;");
            QString firstItem;
            QStringList itemsTot;
            if(richiesta.size()!=0){
                for(int i=0; richiesta.next(); i++) {
                    QString name = richiesta.value(0).toString();
                    if(i==0){
                        firstItem = name;
                    }
                    itemsTot+=name;
                }
                ui->ListWidgetStandardIngredients->clear();
                ui->ListWidgetStandardIngredients->addItems(itemsTot);
                //trovo l'id del primo ingrediente visualizzato
                QSqlQuery richiestaIdFirstItem;
                QString idFirst;
                richiestaIdFirstItem = db.executeQuery("select id_standard_ingredient from Standard_Ingredient where name_ingredient='" + firstItem.replace("\"","\\\"").replace("\'","\\\'") + "' limit 1;");
                for(int i=0; richiestaIdFirstItem.next(); i++) {
                    idFirst = richiestaIdFirstItem.value(0).toString();
                }
                //cerco le ricette che contengono l'ingrediente trovato
                QSqlQuery richiestaRicetteConIngredienteTrovato;
                richiestaRicetteConIngredienteTrovato = db.executeQuery("select distinct title from Recipe join Ingredient on id=id_recipe where id_standard_ingredient=" + idFirst + ";");
                //mentre scorro per caricare le ricette nella lista della UI conto quante ricette ci sono per quell'ingrediente
                int countTot=0;
                QStringList items;
                for(; richiestaRicetteConIngredienteTrovato.next();countTot++){
                    QString nome_ricetta = richiestaRicetteConIngredienteTrovato.value(0).toString();
                    items+=nome_ricetta;
                }
                ui->ListWidgetRecipesContainingIngredient->addItems(items);
                //visualizzo nella ui il numero delle ricette che ci sono per quell'ingrediente
                QString numRicette = QString::number(countTot);
                ui->LabelNumberRecipes->setText("Total numbers of recipes containing the ingredient: " + numRicette);
            }else{
                ui->ListWidgetStandardIngredients->clear();
                ui->ListWidgetStandardIngredients->addItem("No ingredient found");
            }
        }else{
            ui->ListWidgetMatchingResult->clear();
        }
    }else{
        QMessageBox::critical(
            this,
            tr("Database connection error!"),
            tr("Unable to connect to database, check your connection or your database status and retry.") );
        delete ui;
        std::exit(0);
    }
}


void MainWindow::IngredientSelectedFromList(QString ingredienteStandardSelezionato){
    //pulisce gli altri elementi della pagina
    ui->LabelNumberRecipes->setText("Total numbers of recipes containing the ingredient: ");
    ui->ListWidgetRecipesContainingIngredient->clear();
    QCoreApplication::processEvents();
    ui->ListWidgetRecipesContainingIngredient->addItem("Loading result, please wait...");
    // let the application process its events
    QCoreApplication::processEvents();
    //apertura connessione al db e query
    bool ok = db.connectionOk();
    if(ok==true){
        //trovo l'id dell'ingrediente selezionato
        QSqlQuery richiestaIdItem;
        QString idStandardIngredient;
        richiestaIdItem = db.executeQuery("select id_standard_ingredient from Standard_Ingredient where name_ingredient='" + ingredienteStandardSelezionato.replace("\"","\\\"").replace("\'","\\\'") + "' limit 1;");
        for(int i=0; richiestaIdItem.next(); i++) {
            idStandardIngredient = richiestaIdItem.value(0).toString();
        }
        //cerco le ricette che contengono l'ingrediente trovato
        QSqlQuery richiestaRicetteConIngredienteTrovato;
        richiestaRicetteConIngredienteTrovato = db.executeQuery("select distinct title from Recipe join Ingredient on id=id_recipe where id_standard_ingredient=" + idStandardIngredient + ";");
        //mentre scorro per caricare le ricette nella lista della UI conto quante ricette ci sono per quell'ingrediente
        int countTot=0;
        QStringList items;
        for(; richiestaRicetteConIngredienteTrovato.next();countTot++){
            QString nome_ricetta = richiestaRicetteConIngredienteTrovato.value(0).toString();
            items+=nome_ricetta;
        }
        ui->ListWidgetRecipesContainingIngredient->clear();
        ui->ListWidgetRecipesContainingIngredient->addItems(items);
        //visualizzo nella ui il numero delle ricette che ci sono per quell'ingrediente
        QString numRicette = QString::number(countTot);
        ui->LabelNumberRecipes->setText("Total numbers of recipes containing the ingredient: " + numRicette);
    }else{
        QMessageBox::critical(
            this,
            tr("Database connection error!"),
            tr("Unable to connect to database, check your connection or your database status and retry.") );
        delete ui;
        std::exit(0);
    }
}

/* METODI PER STATISTICS PAGE */

void MainWindow::initChartImages(){
    try{
        QChart *recipeWithImages = new QChart;
        recipeWithImages->setTheme(QChart::ChartThemeBlueCerulean);
        QPieSeries *serieRecipeWithImages = new QPieSeries;
        //faccio una query al db cercando il numero di ricette con immagini
        bool ok = db.connectionOk();
        if(ok){
            QSqlQuery richiesta;
            richiesta = db.executeQuery("select count(distinct id_recipe) from Image;");
            int numeroRicetteConImmagini=0;
            while(richiesta.next()){
                numeroRicetteConImmagini=richiesta.value(0).toInt();
            }
            //faccio una query chiedendo il numero totale di ricette e calcolo la differenza
            richiesta = db.executeQuery("select count(*) from Recipe;");
            int numeroRicetteTot=0;
            while(richiesta.next()){
                numeroRicetteTot = richiesta.value(0).toInt();
            }
            int numeroRicetteSenzaImmagini = numeroRicetteTot - numeroRicetteConImmagini;
            //calcolo percentuali
            float percWith = static_cast<float>(numeroRicetteConImmagini)/(static_cast<float>(numeroRicetteTot))*100;
            float percWithout = static_cast<float>(numeroRicetteSenzaImmagini)/(static_cast<float>(numeroRicetteTot))*100;
            QString str;
            serieRecipeWithImages->append("With: " + str.setNum(floor(static_cast<double>(percWith)*100+0.5)/100) + "%", numeroRicetteConImmagini);
            serieRecipeWithImages->append("Without: " + str.setNum(floor(static_cast<double>(percWithout)*100+0.5)/100) + "%", numeroRicetteSenzaImmagini);
            recipeWithImages->addSeries(serieRecipeWithImages);
            recipeWithImages->setTitle(tr("Recipes with images"));
            recipeWithImages->setAnimationOptions(QChart::AllAnimations);
            recipeWithImages->legend()->setAlignment(Qt::AlignBottom);
            recipeWithImages->legend()->setShowToolTips(true);
            // inserisco il chart creato all'interno dell'elemento grafico per visualizzarlo
            ui->RecipeWithImagesPieChart->setChart(recipeWithImages);
            // collego l'evento hovered (come onMouseOver) su una fetta del grafico con il metodo per visualizzare il numero preciso invece della percentuale
            connect(serieRecipeWithImages, &QPieSeries::hovered, this, &MainWindow::mostraNumSlice);
        }else{
            QMessageBox::critical(
                this,
                tr("Database connection error!"),
                tr("Unable to connect to database, check your connection or your database status and retry.") );
            delete ui;
            std::exit(0);
        }
    }catch(...){
        QMessageBox::critical(
          this,
          tr("Chart creation error!"),
          tr("Sorry, an error has occured while creating the charts. Please retry.") );
    }
}

// mostra il valore preciso della fetta (slice) del grafico a torta invece della percentuale
void MainWindow::mostraNumSlice(QPieSlice *slice){
    if(slice->isLabelVisible()==true){
        slice->setLabelVisible(false);
        slice->setLabel(label_iniziale);
    }else{
        label_iniziale = slice->label();
        QString numeroDaVisualizzare = QString::number(slice->value());
        slice->setLabel(numeroDaVisualizzare);
        slice->setLabelVisible(true);
    }
}

void MainWindow::initChartRecipePartition(){
    try{
        QChart *recipePartition = new QChart;
        recipePartition->setTheme(QChart::ChartThemeBlueCerulean);
        QPieSeries *serieRecipePartition = new QPieSeries;
        //faccio una query al db cercando il numero di ricette con immagini
        bool ok = db.connectionOk();
        if(ok){
            QSqlQuery richiesta;
            richiesta = db.executeQuery("select count(*) from Recipe where partition_type='train';");
            int numeroRicetteTrain=0;
            while(richiesta.next()){
                numeroRicetteTrain=richiesta.value(0).toInt();
            }
            richiesta = db.executeQuery("select count(*) from Recipe where partition_type='test';");
            int numeroRicetteTest=0;
            while(richiesta.next()){
                numeroRicetteTest=richiesta.value(0).toInt();
            }
            richiesta = db.executeQuery("select count(*) from Recipe where partition_type='val';");
            int numeroRicetteVal=0;
            while(richiesta.next()){
                numeroRicetteVal=richiesta.value(0).toInt();
            }
            //calcolo percentuali
            float percTrain = static_cast<float>(numeroRicetteTrain)/((static_cast<float>(numeroRicetteVal)+static_cast<float>(numeroRicetteTest)+static_cast<float>(numeroRicetteTrain)))*100;
            float percTest = static_cast<float>(numeroRicetteTest)/((static_cast<float>(numeroRicetteVal)+static_cast<float>(numeroRicetteTest)+static_cast<float>(numeroRicetteTrain)))*100;
            float percVal = static_cast<float>(numeroRicetteVal)/((static_cast<float>(numeroRicetteVal)+static_cast<float>(numeroRicetteTest)+static_cast<float>(numeroRicetteTrain)))*100;
            QString str;
            serieRecipePartition->append("Train: " + str.setNum(floor(static_cast<double>(percTrain)*100+0.5)/100) + "%", numeroRicetteTrain);
            serieRecipePartition->append("Test: " + str.setNum(floor(static_cast<double>(percTest)*100+0.5)/100) + "%", numeroRicetteTest);
            serieRecipePartition->append("Val: " + str.setNum(floor(static_cast<double>(percVal)*100+0.5)/100) + "%", numeroRicetteVal);
            recipePartition->addSeries(serieRecipePartition);
            recipePartition->setTitle(tr("Recipes partitions"));
            recipePartition->setAnimationOptions(QChart::AllAnimations);
            recipePartition->legend()->setAlignment(Qt::AlignBottom);
            recipePartition->legend()->setShowToolTips(true);
            // inserisco il chart creato all'interno dell'elemento grafico per visualizzarlo
            ui->RecipePartitionsPieChart->setChart(recipePartition);
            // collego l'evento hovered (come onMouseOver) su una fetta del grafico con il metodo per visualizzare il numero preciso invece della percentuale
            connect(serieRecipePartition, &QPieSeries::hovered, this, &MainWindow::mostraNumSlice);
        }else{
            QMessageBox::critical(
                this,
                tr("Database connection error!"),
                tr("Unable to connect to database, check your connection or your database status and retry.") );
            delete ui;
            std::exit(0);
        }
    }catch(...){
        QMessageBox::critical(
          this,
          tr("Chart creation error!"),
          tr("Sorry, an error has occured while creating the charts. Please retry.") );
    }
}

void MainWindow::initChartIngredientValid(){
    try{
        QChart *ingredientValid = new QChart;
        ingredientValid->setTheme(QChart::ChartThemeBlueCerulean);
        QPieSeries *serieIngredientValid = new QPieSeries;
        //faccio una query al db cercando il numero di ricette con immagini
        bool ok = db.connectionOk();
        if(ok){
            QSqlQuery richiesta;
            richiesta = db.executeQuery("select count(*) from Standard_Ingredient where valid=true;");
            int numIngredientValid=0;
            while(richiesta.next()){
                numIngredientValid=richiesta.value(0).toInt();
            }
            richiesta = db.executeQuery("select count(*) from Standard_Ingredient where valid=false;");
            int numIngredientNotValid=0;
            while(richiesta.next()){
                numIngredientNotValid=richiesta.value(0).toInt();
            }
            //calcolo percentuali
            float percValid = static_cast<float>(numIngredientValid)/(static_cast<float>(numIngredientValid)+static_cast<float>(numIngredientNotValid))*100;
            float percNotValid = static_cast<float>(numIngredientNotValid)/(static_cast<float>(numIngredientValid)+static_cast<float>(numIngredientNotValid))*100;
            QString str;
            serieIngredientValid->append("Valid: " + str.setNum(floor(static_cast<double>(percValid)*100+0.5)/100) + "%", numIngredientValid);
            serieIngredientValid->append("Not Valid: " + str.setNum(floor(static_cast<double>(percNotValid)*100+0.5)/100) + "%", numIngredientNotValid);
            ingredientValid->addSeries(serieIngredientValid);
            ingredientValid->setTitle(tr("Standard Ingredients Valid"));
            ingredientValid->setAnimationOptions(QChart::AllAnimations);
            ingredientValid->legend()->setAlignment(Qt::AlignBottom);
            ingredientValid->legend()->setShowToolTips(true);
            // inserisco il chart creato all'interno dell'elemento grafico per visualizzarlo
            ui->IngredientValidPieChart->setChart(ingredientValid);
            // collego l'evento hovered (come onMouseOver) su una fetta del grafico con il metodo per visualizzare il numero preciso invece della percentuale
            connect(serieIngredientValid, &QPieSeries::hovered, this, &MainWindow::mostraNumSlice);
        }else{
            QMessageBox::critical(
                this,
                tr("Database connection error!"),
                tr("Unable to connect to database, check your connection or your database status and retry.") );
            delete ui;
            std::exit(0);
        }
    }catch(...){
        QMessageBox::critical(
          this,
          tr("Chart creation error!"),
          tr("Sorry, an error has occured while creating the charts. Please retry.") );
    }
}

void MainWindow::initChartTopIngredientsForRecipe(){
    try{
        QBarSeries *series = new QBarSeries();
        //QStringList categories;
        QStringList numeri;
        bool ok = db.connectionOk();
        if(ok){
            QSqlQuery richiesta;
            richiesta = db.executeQuery("select * from Top5RecipesForIngredient;");
            // Qui sotto la vecchia query, prima della creazione della Materialized View
            //richiesta = db.executeQuery("select count(*), id_recipe from Ingredient group by id_recipe order by count(*) desc limit 5;");
            QBarSet *set0;
            for(int i=0;richiesta.next();i++){
                int numeroIngredienti = richiesta.value(0).toInt();
                QString id_recipe = richiesta.value(1).toString();
                // richiede il titolo della ricetta da visualizzare nella legenda
                QSqlQuery query_title;
                query_title = db.executeQuery("select title from Recipe where id='" + id_recipe + "';");
                QString titleRicetta;
                while(query_title.next()){
                    titleRicetta=query_title.value(0).toString();
                }
                /*per porre a 0 tutti i valori della serie interessata eccetto quello in cui andrà inserito il valore
                  es: serie1: valore, 0, 0, 0, 0   serie2: 0, valore, 0, 0, 0  serie3: 0, 0, valore, 0, 0  ecc...
                  in questo modo sarà possibile visualizzare un valore per ogni serie, ed ogni serie ha un colore diverso,
                  quindi un colore diverso per ogni valore */
                set0 = new QBarSet(titleRicetta);
                for(int j=0;j<i;j++){
                    *set0 << 0;
                }
                *set0 << numeroIngredienti;
                series->append(set0);
                numeri << QString::number(numeroIngredienti);
            }
            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Top 5 Recipes with more ingredients");
            chart->setAnimationOptions(QChart::SeriesAnimations);
            // sull'asse X il numero preciso degli ingredienti
            QBarCategoryAxis *axisX = new QBarCategoryAxis();
            axisX->append(numeri);
            chart->addAxis(axisX, Qt::AlignBottom);
            series->attachAxis(axisX);
            // sull'asse Y una scala di valori
            QValueAxis *axisY = new QValueAxis();
            chart->addAxis(axisY, Qt::AlignLeft);
            series->attachAxis(axisY);
            // legenda visibile e con tooltips attivati per mostrare al passaggio del mouse il nome completo delle ricette che sono state abbreviate con '...'
            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignRight);
            chart->legend()->setShowToolTips(true);
            //assegno il chart creato all'elemento della UI per visualizzarlo
            ui->TopRecipesWithMoreIngredientsHistogram->setChart(chart);
        }else{
            QMessageBox::critical(
                this,
                tr("Database connection error!"),
                tr("Unable to connect to database, check your connection or your database status and retry.") );
            delete ui;
            std::exit(0);
        }
    }catch(...){
        QMessageBox::critical(
          this,
          tr("Chart creation error!"),
          tr("Sorry, an error has occured while creating the charts. Please retry.") );
    }
}

void MainWindow::initChartTopInstructionsForRecipe(){
    try{
        QBarSeries *series = new QBarSeries();
        QStringList numeri;
        bool ok = db.connectionOk();
        if(ok){
            QSqlQuery richiesta;
            // Qui sotto la vecchia query, prima della creazione della Materialized View
            //richiesta = db.executeQuery("select count(id_instruction), id_recipe from Instruction group by id_recipe order by count(id_instruction) desc limit 5;");
            richiesta = db.executeQuery("select * from Top5RecipesForInstruction");
            QBarSet *set0;
            for(int i=0;richiesta.next();i++){
                int numeroIstruzioni = richiesta.value(0).toInt();
                QString id_recipe = richiesta.value(1).toString();
                // richiede il titolo della ricetta da visualizzare nella legenda
                QSqlQuery query_title;
                query_title = db.executeQuery("select title from Recipe where id='" + id_recipe + "';");
                QString titleRicetta;
                /*per porre a 0 tutti i valori della serie interessata eccetto quello in cui andrà inserito il valore
                  es: serie1: valore, 0, 0, 0, 0   serie2: 0, valore, 0, 0, 0  serie3: 0, 0, valore, 0, 0  ecc...
                  in questo modo sarà possibile visualizzare un valore per ogni serie, ed ogni serie ha un colore diverso,
                  quindi un colore diverso per ogni valore */
                while(query_title.next()){
                    titleRicetta=query_title.value(0).toString();
                }
                set0 = new QBarSet(titleRicetta);
                for(int j=0;j<i;j++){
                    *set0 << 0;
                }
                *set0 << numeroIstruzioni;
                series->append(set0);
                numeri << QString::number(numeroIstruzioni);
            }
            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Top 5 Recipes with more instructions");
            chart->setAnimationOptions(QChart::SeriesAnimations);
            // sull'asse X il numero preciso delle istruzioni
            QBarCategoryAxis *axisX = new QBarCategoryAxis();
            axisX->append(numeri);
            QFont f;
            f.setPixelSize(11);
            axisX->setLabelsFont(f);
            chart->addAxis(axisX, Qt::AlignBottom);
            series->attachAxis(axisX);
            // sull'asse Y una scala di valori
            QValueAxis *axisY = new QValueAxis();
            chart->addAxis(axisY, Qt::AlignLeft);
            series->attachAxis(axisY);
            // legenda visibile e con tooltips attivati per mostrare al passaggio del mouse il nome completo delle ricette che sono state abbreviate con '...'
            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignRight);
            chart->legend()->setShowToolTips(true);
            //assegno il chart creato all'elemento della UI per visualizzarlo
            ui->TopRecipesWithMoreInstructionsHistogram->setChart(chart);
        }else{
            QMessageBox::critical(
                this,
                tr("Database connection error!"),
                tr("Unable to connect to database, check your connection or your database status and retry.") );
            delete ui;
            std::exit(0);
        }
    }catch(...){
        QMessageBox::critical(
          this,
          tr("Chart creation error!"),
          tr("Sorry, an error has occured while creating the charts. Please retry.") );
    }
}

void MainWindow::searchButtonInStatisticsPagePressed(){
    try{
        QString testoDaCercare = ui->LineEditSearchNumberRecipesForIngredients->text();
        // nel caso il testo da cercare sia vuoto chiedo conferma all'utente tramite una finestra di alert che voglia cercare in tutto il db dato che ci impiegherà molto tempo
        bool testoDaCercareSure = true;
        if(testoDaCercare.length()==0 || testoDaCercare.toStdString()==""){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Are you sure?", "Are you sure to search all the ingredients in the database? It can requires even one minute!", QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                testoDaCercareSure = true;
            } else {
                testoDaCercareSure = false;
            }
        }
        // visualizzo un messaggio di attesa all'interno della tabella
        ui->NumberRecipesForStdIngredientTable->setRowCount(1);
        QCoreApplication::processEvents();
        ui->NumberRecipesForStdIngredientTable->setItem(0,0,new QTableWidgetItem("Loading result"));
        ui->NumberRecipesForStdIngredientTable->setItem(0,1,new QTableWidgetItem("Please wait..."));
        QCoreApplication::processEvents();
        //apertura connessione al db e query
        bool ok = db.connectionOk();
        if(ok==true){
            if(testoDaCercareSure==true){
                int righeTotali=0;
                QSqlQuery richiesta_ingredientiStd;
                // eseguo una prima query per capire quante dovranno essere le righe della tabella
                richiesta_ingredientiStd = db.executeQuery("select name_ingredient, id_standard_ingredient from Standard_Ingredient where name_ingredient like '%" + testoDaCercare.replace("\"","\\\"").replace("\'","\\\'") + "%';");
                ui->NumberRecipesForStdIngredientTable->setRowCount(0);
                if(richiesta_ingredientiStd.size()!=0){
                    while(richiesta_ingredientiStd.next()){
                        righeTotali++;
                    }
                    // assegno alla tabella le righe contate
                    ui->NumberRecipesForStdIngredientTable->setRowCount(righeTotali);
                    // eseguo una seconda volta la query per inserire i dati nelle righe della tabella
                    richiesta_ingredientiStd = db.executeQuery("select name_ingredient, id_standard_ingredient from Standard_Ingredient where name_ingredient like '%" + testoDaCercare.replace("\"","\\\"").replace("\'","\\\'") + "%';");
                    for(int riga=0; richiesta_ingredientiStd.next(); riga++) {
                        QString name = richiesta_ingredientiStd.value(0).toString();
                        QString id = richiesta_ingredientiStd.value(1).toString();
                        QSqlQuery richiesta_numero;
                        // per ogni ingrediente trovato calcolo quante ricette contengono tale ingrediente
                        richiesta_numero = db.executeQuery("select count(*) from Ingredient where id_standard_ingredient=" + id + ";");
                        int numero_ricette=0;
                        while(richiesta_numero.next()){
                            numero_ricette = richiesta_numero.value(0).toInt();
                        }
                        // riempio la riga della tabella con il nome dell'ingrediente nella prima colonna
                        QTableWidgetItem *itemName = new QTableWidgetItem(name);
                        itemName->setFlags(itemName->flags() ^ Qt::ItemIsEditable);
                        ui->NumberRecipesForStdIngredientTable->setItem(riga,0,itemName);
                        // riempio la riga della tabella con il numero delle ricette che contengono l'ingrediente nella seconda colonna
                        QTableWidgetItem *itemNumber = new QTableWidgetItem;
                        itemNumber->setData(Qt::EditRole, numero_ricette);
                        itemNumber->setFlags(itemNumber->flags() ^ Qt::ItemIsEditable);
                        ui->NumberRecipesForStdIngredientTable->setItem(riga,1,itemNumber);
                    }
                    ui->NumberRecipesForStdIngredientTable->sortByColumn(1,Qt::DescendingOrder);
                }else{
                    ui->NumberRecipesForStdIngredientTable->setRowCount(1);
                    ui->NumberRecipesForStdIngredientTable->setItem(0,0,new QTableWidgetItem("No ingredient found"));
                    ui->NumberRecipesForStdIngredientTable->setItem(0,1,new QTableWidgetItem(""));
                }
            }else{
                ui->NumberRecipesForStdIngredientTable->setRowCount(0);
            }
        }else{
            QMessageBox::critical(
                this,
                tr("Database connection error!"),
                tr("Unable to connect to database, check your connection or your database status and retry.") );
            delete ui;
            std::exit(0);
        }
    }catch(...){
        QMessageBox::critical(
          this,
          tr("Table creation error!"),
          tr("Sorry, an error has occured while creating the ingredient table. Please retry.") );
    }
}

void MainWindow::initStatisticsPage(){
    if(statisticsPageAlreadyVisited==false){
        initChartImages();
        initChartRecipePartition();
        initChartIngredientValid();
        initChartTopIngredientsForRecipe();
        initChartTopInstructionsForRecipe();
        ui->NumberRecipesForStdIngredientTable->horizontalHeader()->setStretchLastSection(true);
    }
}

/* UTILI */

//pulisce tutti gli elementi in RecipePage
void MainWindow::cleanRecipePage(){
    ui->ListWidgetMatchingResult->clear();
    ui->LineEditSearchRecipe->clear();
    ui->ListWidgetIngredients->clear();
    ui->ListWidgetInstructions->clear();
    ui->ImageLabel->clear();
}
//pulisce tutti gli elementi in IngredientPage
void MainWindow::cleanIngredientPage(){
    ui->LabelNumberRecipes->setText("Total numbers of recipes containing the ingredient: ");
    ui->LineEditSearchIngredient->clear();
    ui->ListWidgetStandardIngredients->clear();
    ui->ListWidgetRecipesContainingIngredient->clear();
}


/* SLOTS */
void MainWindow::on_IngredientSearchButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_RecipeSearchButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_StatisticsButton_clicked()
{
    // visualizza una scritta di attesa nella label della home page
    QCoreApplication::processEvents();
    ui->labelWaitStatistics->setText("Just a moment please...");
    ui->labelWaitStatistics->setMaximumSize(16777215,20);
    QCoreApplication::processEvents();
    // carica la pagina statistics
    initStatisticsPage();
    // setta a true il fatto che la pagina statistics sia già stata visitata e quindi caricata
    statisticsPageAlreadyVisited=true;
    ui->stackedWidget->setCurrentIndex(3);
    ui->labelWaitStatistics->setText("");
    ui->labelWaitStatistics->setMaximumSize(16777215,20);
}

void MainWindow::on_HomeButtonInRecipePage_clicked()
{
    cleanRecipePage();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_SearchButtonInRecipePage_clicked()
{
    searchButtonInRecipePagePressed();
}

void MainWindow::on_ListWidgetMatchingResult_itemDoubleClicked(QListWidgetItem *item)
{
    QString nomeRicettaSelezionata = item->text();
    if(nomeRicettaSelezionata!="No recipe found"){
        RecipeSelectedFromList(nomeRicettaSelezionata);
    }
}

void MainWindow::on_HomeButtonInIngredientPage_clicked()
{
    cleanIngredientPage();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_SearchButtonInIngredientPage_clicked()
{
    searchButtonInIngredientPagePressed();
}

void MainWindow::on_ListWidgetStandardIngredients_itemDoubleClicked(QListWidgetItem *item)
{
    QString nomeIngredienteStandardSelezionato = item->text();
    if(nomeIngredienteStandardSelezionato!="No ingredient found"){
        IngredientSelectedFromList(nomeIngredienteStandardSelezionato);
    }
}

// doppio click su una ricetta nella pagina ingredienti porta alla pagina ricette con quella ricetta selezionata
void MainWindow::on_ListWidgetRecipesContainingIngredient_itemDoubleClicked(QListWidgetItem *item)
{
    ui->stackedWidget->setCurrentIndex(1);
    QString nomeRicettaSelezionata = item->text();
    if(nomeRicettaSelezionata!="No recipe found"){
        // svuoto la pagina recipe da ricerche precedenti
        cleanRecipePage();
        // inserisco la ricetta che si è cliccata nella pagina recipe
        ui->ListWidgetMatchingResult->addItem(item->text());
        // faccio caricare gli elementi collegati alla ricetta selezionata
        RecipeSelectedFromList(nomeRicettaSelezionata);
    }
}

// doppio click su un ingrediente nella pagina ricette porta alla pagina ingredienti con quell'ingrediente selezionato
void MainWindow::on_ListWidgetIngredients_itemDoubleClicked(QListWidgetItem *item)
{
    ui->stackedWidget->setCurrentIndex(2);
    QString nomeIngredienteSelezionato = item->text();
    //cerco il nome standard ingredient a partire dal nome ingredient selezionato
    bool ok = db.connectionOk();
    if(ok){
        QSqlQuery richiestaIdItem;
        QString nameStandardIngredient;
        richiestaIdItem = db.executeQuery("select Standard_Ingredient.name_ingredient from Ingredient join Standard_Ingredient on Ingredient.id_standard_ingredient=Standard_Ingredient.id_standard_ingredient where description='" + nomeIngredienteSelezionato.replace("\"","\\\"").replace("\'","\\\'") + "' limit 1;");
        for(int i=0; richiestaIdItem.next(); i++) {
            nameStandardIngredient = richiestaIdItem.value(0).toString();
        }
        // svuoto la pagina ingredient da altre ricerche precedenti
        cleanIngredientPage();
        // inserisco l'ingrediente standard appena trovato nella pagina ingredient
        ui->ListWidgetStandardIngredients->addItem(nameStandardIngredient);
        // faccio caricare le ricette che contengono quell'ingrediente
        IngredientSelectedFromList(nameStandardIngredient);
    }else{
        QMessageBox::critical(
            this,
            tr("Database connection error!"),
            tr("Unable to connect to database, check your connection or your database status and retry.") );
        delete ui;
        std::exit(0);
    }
}

void MainWindow::on_HomeButtonInStatisticsPage_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_SearchButtonInStatisticsPage_clicked()
{
    searchButtonInStatisticsPagePressed();
}

void MainWindow::on_actionRecipe_Search_Page_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_actionIngredient_Search_Page_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_actionStatistics_Page_triggered()
{
    initStatisticsPage();
    statisticsPageAlreadyVisited=true;
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_NextButton_clicked()
{
    loadNextImage();
}

void MainWindow::on_PreviousButton_clicked()
{
    loadPreviousImage();
}

void MainWindow::on_LineEditSearchRecipe_returnPressed()
{
    searchButtonInRecipePagePressed();
}

void MainWindow::on_LineEditSearchIngredient_returnPressed()
{
    searchButtonInIngredientPagePressed();
}

void MainWindow::on_LineEditSearchNumberRecipesForIngredients_returnPressed()
{
    searchButtonInStatisticsPagePressed();
}
