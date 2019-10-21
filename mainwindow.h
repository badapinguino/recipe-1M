#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "filedownloader.h"
#include "databaseconnection.h"
#include <QMainWindow>
#include <QSqlDatabase>
#include <QtSql>
#include <QListWidgetItem>
#include <QtCharts>

namespace Ui {
class MainWindow;
}
/**
    Classe MainWindow utilizzata come classe principale, è la classe con i metodi usati per mostrare le
    informazioni negli elementi grafici.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
        Costruttore che richiama il metodo setupIniziale() e visualizza la UI.
        @param parent Puntatore al widget che viene usato come main window.
    */
    explicit MainWindow(QWidget *parent = nullptr);
    /**
        Distruttore della classe MainWindow.
    */
    ~MainWindow();

private slots:
    /**
        Slot che permette di passare alla Ingredient Search Page.
    */
    void on_IngredientSearchButton_clicked();
    /**
        Slot che permette di passare alla Recipe Search Page.
    */
    void on_RecipeSearchButton_clicked();

    /**
        Slot che permette di passare alla Statistics Page.
    */
    void on_StatisticsButton_clicked();

    /**
        Slot che permette di passare alla Home Page partendo dalla Recipe Search Page.
    */
    void on_HomeButtonInRecipePage_clicked();

    /**
        Slot che richiama il metodo searchButtonInRecipePagePressed().
    */
    void on_SearchButtonInRecipePage_clicked();

    /**
        Slot che richiama il metodo RecipeSelectedFromList(nomeRicettaSelezionato).
        @param item È il QListWidgetItem della lista che è stato selezionato dall'utente.
    */
    void on_ListWidgetMatchingResult_itemDoubleClicked(QListWidgetItem *item);

    /**
        Slot che permette di passare alla Home Page partendo dalla Ingredient Search Page.
    */
    void on_HomeButtonInIngredientPage_clicked();

    /**
        Slot che richiama il metodo searchButtonInIngredientPagePressed().
    */
    void on_SearchButtonInIngredientPage_clicked();

    /**
        Slot che richiama il metodo IngredientSelectedFromList(nomeIngredienteStandardSelezionato), il cui parametro è una
        stringa estrapolata dall'item passato in ingresso alla funzione slot.
        @param item È il QListWidgetItem della lista che è stato selezionato dall'utente.
    */
    void on_ListWidgetStandardIngredients_itemDoubleClicked(QListWidgetItem *item);

    /**
        Slot che viene attivato con un doppio click su una ricetta nella pagina Ingredient Search,
        e che porta alla pagina Recipe Search con quella ricetta selezionata.
        @param item È il QListWidgetItem della lista che è stato selezionato dall'utente.
    */
    void on_ListWidgetRecipesContainingIngredient_itemDoubleClicked(QListWidgetItem *item);

    /**
        Slot che viene attivato con un doppio click su un ingrediente nella pagina Recipe Search,
        e che porta alla pagina Ingredient Search con quell'ingrediente selezionato.
        @param item È il QListWidgetItem della lista che è stato selezionato dall'utente.
    */
    void on_ListWidgetIngredients_itemDoubleClicked(QListWidgetItem *item);

    /**
        Slot che permette di passare alla Home Page partendo dalla Statistics Page
    */
    void on_HomeButtonInStatisticsPage_clicked();

    /**
        Slot che richiama il metodo searchButtonInStatisticsPagePressed().
    */
    void on_SearchButtonInStatisticsPage_clicked();

    /**
        Slot che permette di passare alla Recipe Search Page attraverso il menù a tendina.
    */
    void on_actionRecipe_Search_Page_triggered();

    /**
        Slot che permette di passare alla Ingredient Search Page attraverso il menù a tendina.
    */
    void on_actionIngredient_Search_Page_triggered();

    /**
        Slot che permette di passare alla Statistics Page attraverso il menù a tendina.
    */
    void on_actionStatistics_Page_triggered();

    /**
        Slot che richiama il metodo loadNextImage().
    */
    void on_NextButton_clicked();

    /**
        Slot che richiama il metodo loadPreviousImage().
    */
    void on_PreviousButton_clicked();

    /**
        Slot che richiama il metodo searchButtonInRecipePagePressed(), permettendo di usare il tasto invio al posto del pulsante Search.
    */
    void on_LineEditSearchRecipe_returnPressed();

    /**
        Slot che richiama il metodo searchButtonInIngredientPagePressed(), permettendo di usare il tasto invio al posto del pulsante Search.
    */
    void on_LineEditSearchIngredient_returnPressed();

    /**
        Slot che richiama il metodo searchButtonInStatisticsPagePressed(), permettendo di usare il tasto invio al posto del pulsante Search.
    */
    void on_LineEditSearchNumberRecipesForIngredients_returnPressed();

private:
    Ui::MainWindow *ui;
    DatabaseConnection db;
    bool statisticsPageAlreadyVisited;
    QString label_iniziale;
    QString urlImmagineVisualizzata="";
    QStringList listaUrlImmagini;

    /**
        Metodo che configura la grafica dell'applicazione con anche i relativi colori e dimensioni dei font, e verifica la presenza di connessione al database.
        @brief Configura la grafica e verifica la connessione al database.
    */
    void setupIniziale();

    /**
        Metodo relativo alla pagina Recipe Search che viene richiamato quando il pulsante di ricerca viene premuto,
        ha il compito di pulire gli elementi nella pagina eccetto l'elenco delle ricette, recuperare il testo che l'utente vuole cercare,
        cercare nel database se esistono ricette con il testo cercato nel loro titolo e visualizzarle nella pagina.
        Dopo averle visualizzate recupera gli ingredienti, il procedimento e le immagini relative alla prima ricetta trovata
        e visualizza il tutto inserendolo nella pagina Recipe Search.
        @brief Cerca le ricette con una stringa cercata dall'utente nel titolo e le visualizza, inoltre seleziona la prima ricetta trovata e ne visualizza le informazioni collegate.
    */
    void searchButtonInRecipePagePressed();

    /**
        Metodo relativo alla pagina Ingredient Search che viene richiamato quando il pulsante di ricerca viene premuto,
        ha il compito di pulire gli elementi nella pagina, recuperare il testo che l'utente vuole cercare,
        cercare nel database se esistono ingredienti standard con il testo cercato nel loro nome e visualizzarli nella pagina.
        Dopo averli visualizzati recupera le ricette in cui è presente tra gli ingredienti il primo ingrediente standard trovato
        e visualizza il tutto inserendolo nella pagina Ingredient Search.
        @brief Cerca gli ingredienti standard con nel nome una stringa cercata dall'utente e li visualizza, inoltre seleziona il primo ingrediente e visualizza le ricette che lo utilizzano.
    */
    void searchButtonInIngredientPagePressed();

    /**
        Metodo relativo alla pagina Recipe Search che viene richiamato quando un utente effettua un doppio click su una ricetta in elenco,
        ha il compito di pulire gli elementi nella pagina, poi recupera gli ingredienti, il procedimento e le immagini relative
        a tale ricetta e visualizza il tutto inserendolo nella pagina Recipe Search.
        @brief Visualizza le informazioni collegate alla ricetta selezionata dall'utente.
        @param nomeIngredienteSelezionato Una QString con il titolo dell'ingrediente selezionato.
    */
    void RecipeSelectedFromList(QString nomeIngredienteSelezionato);

    /**
        Metodo relativo alla pagina Ingredient Search che viene richiamato quando un utente effettua un doppio click su un ingrediente standard in elenco,
        ha il compito di pulire gli elementi nella pagina eccetto l'elenco degli ingredienti,
        poi recupera gli ingredienti, il procedimento e le immagini relative
        a tale ricetta e visualizza il tutto inserendolo nella pagina Recipe Search.
        @brief Visualizza le informazioni collegate alla ricetta selezionata dall'utente.
        @param ingredienteStandardSelezionato Una QString con il nome dell'ingrediente selezionato.
    */
    void IngredientSelectedFromList(QString ingredienteStandardSelezionato);

    /**
        Metodo della pagina Statistics che inizializza il grafico a torta relativo al numero delle ricette con immagini vs il numero di ricette senza immagini.
        Per inizializzarlo effettua due query che chiedono appunto il numero di ricette con immagini, ed il numero di ricette totali,
        sottraendo il numero di ricette con immagini al numero di ricette totali si ottiene il numero di ricette senza immagini.
        Tali risultati vengono poi inseriti in due diverse QPieSlice, calcolata la percentuale e visualizzate nell'elemento grafico
        corrispondente.
        @brief Inizializza il grafico a torta del numero di ricette con immagini vs il numero di ricette senza immagini.
    */
    void initChartImages();

    /**
        Metodo che inizializza la pagina Statistics richiamando i metodi di inizializzazione dei vari grafici all'interno della pagina.
        Se la pagina è già stata caricata precedentemente allora il contenuto di questo metodo non viene rieseguito.
        @brief Inizializza il contenuto della pagina Statistics, se non è già stata caricata.
    */
    void initStatisticsPage();

    /**
        Metodo che pulisce tutti gli elementi in Recipe Search Page.
    */
    void cleanRecipePage();

    /**
        Metodo che pulisce tutti gli elementi in Ingredient Search Page.
    */
    void cleanIngredientPage();

    /**
        Mostra nella legenda il valore preciso della fetta del grafico a torta, al posto della percentuale.
        @param slice La fetta (QPieSlice) il cui valore della legenda deve cambiare
    */
    void mostraNumSlice(QPieSlice *slice);

    /**
        Metodo della pagina Statistics che inizializza il grafico a torta relativo alla suddivisione tra ingredienti standard validi vs non validi.
        Per inizializzarlo effettua due query che chiedono il numero di ingredienti standard con valore valid=true e valid=false.
        Tali risultati vengono poi inseriti in due diverse QPieSlice, ne viene calcolata la percentuale e vengono poi
        visualizzate nell'elemento grafico corrispondente.
        @brief Inizializza il grafico a torta relativo alla suddivisione tra ingredienti standard validi vs non validi.
    */
    void initChartIngredientValid();

    /**
        Metodo della pagina Statistics che inizializza il grafico a torta relativo alla suddivisione in partizioni delle ricette.
        Per inizializzarlo effettua tre query che chiedono appunto il numero di ricette con partizione 'train', 'test' e 'val'.
        Tali risultati vengono poi inseriti in tre diverse QPieSlice, ne viene calcolata la percentuale e vengono poi
        visualizzate nell'elemento grafico corrispondente.
        @brief Inizializza il grafico a torta relativo alla suddivisione in partizioni delle ricette.
    */
    void initChartRecipePartition();

    /**
        Metodo che inizializza l'istogramma relativo alla top 5 delle ricette per numero degli ingredienti.
        Richiede al database la classifica di questa top 5 (memorizzata come vista materializzata) ed inserisce i valori
        trovati in differenti serie che vengono poi aggiunte al grafico e visualizzate nell'elemento grafico corrispondente.
        @brief Inizializza l'istogramma della top 5 delle ricette per numero degli ingredienti.
    */
    void initChartTopIngredientsForRecipe();

    /**
        Metodo che inizializza l'istogramma relativo alla top 5 delle ricette per numero di istruzioni.
        Richiede al database la classifica di questa top 5 (memorizzata come vista materializzata) ed inserisce i valori
        trovati in differenti serie che vengono poi aggiunte al grafico e visualizzate nell'elemento grafico corrispondente.
        @brief Inizializza l'istogramma della top 5 delle ricette per numero di istruzioni.
    */
    void initChartTopInstructionsForRecipe();

    /**
        Metodo relativo alla pagina Statistics che viene richiamato quando il pulsante di ricerca viene premuto,
        ha il compito di pulire la tabella da eventuali altre ricerche, recuperare il testo che l'utente vuole cercare,
        cercare nel database se esistono ingredienti standard con il testo cercato nel loro nome e visualizzarli nella pagina
        assieme al numero delle ricette per ogni ingrediente standard trovato. Vengono visualizzati in una tabella in ordine decrescente.
        @brief Cerca gli ingredienti standard con nel nome una stringa cercata dall'utente e li visualizza assieme al numero delle ricette in cui vengono utilizzati.
    */
    void searchButtonInStatisticsPagePressed();

    /**
        Metodo per caricare l'immagine precedente nella pagina Recipe Search, viene attivato quando l'utente clicca sul pulsante Previous.
        Carica l'immagine precedente, se presente, altrimenti se è visualizzata la prima immagine carica la ultima disponibile.
        @brief Carica l'immagine precedente nella pagina Recipe Search.
    */
    void loadPreviousImage();

    /**
        Metodo per caricare l'immagine successiva nella pagina Recipe Search, viene attivato quando l'utente clicca sul pulsante Next.
        Carica l'immagine successiva, se presente, altrimenti se è visualizzata l'ultima immagine disponibile carica la prima immagine.
        @brief Carica l'immagine successiva nella pagina Recipe Search.
    */
    void loadNextImage();
};

#endif // MAINWINDOW_H
