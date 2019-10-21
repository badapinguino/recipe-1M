/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "QtCharts"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRecipe_Search_Page;
    QAction *actionIngredient_Search_Page;
    QAction *actionStatistics_Page;
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *mainPage;
    QGridLayout *gridLayout_3;
    QWidget *widget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *RecipeSearchButton;
    QPushButton *IngredientSearchButton;
    QPushButton *StatisticsButton;
    QLabel *labelWaitStatistics;
    QLabel *labelTitle;
    QWidget *recipeSearchPage;
    QGridLayout *gridLayout_5;
    QListWidget *ListWidgetIngredients;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *HomeButtonInRecipePage;
    QLineEdit *LineEditSearchRecipe;
    QPushButton *SearchButtonInRecipePage;
    QPushButton *PreviousButton;
    QListWidget *ListWidgetMatchingResult;
    QListWidget *ListWidgetInstructions;
    QPushButton *NextButton;
    QLabel *ImageLabel;
    QWidget *ingredientSearchPage;
    QGridLayout *gridLayout_6;
    QLabel *LabelNumberRecipes;
    QListWidget *ListWidgetRecipesContainingIngredient;
    QListWidget *ListWidgetStandardIngredients;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *HomeButtonInIngredientPage;
    QLineEdit *LineEditSearchIngredient;
    QPushButton *SearchButtonInIngredientPage;
    QWidget *statisticsPage;
    QGridLayout *gridLayout_4;
    QChartView *TopRecipesWithMoreIngredientsHistogram;
    QChartView *RecipePartitionsPieChart;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *HomeButtonInStatisticsPage;
    QLineEdit *LineEditSearchNumberRecipesForIngredients;
    QPushButton *SearchButtonInStatisticsPage;
    QChartView *RecipeWithImagesPieChart;
    QChartView *IngredientValidPieChart;
    QChartView *TopRecipesWithMoreInstructionsHistogram;
    QTableWidget *NumberRecipesForStdIngredientTable;
    QMenuBar *menuBar;
    QMenu *menuRecipe1M;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(831, 516);
        actionRecipe_Search_Page = new QAction(MainWindow);
        actionRecipe_Search_Page->setObjectName(QString::fromUtf8("actionRecipe_Search_Page"));
        actionIngredient_Search_Page = new QAction(MainWindow);
        actionIngredient_Search_Page->setObjectName(QString::fromUtf8("actionIngredient_Search_Page"));
        actionStatistics_Page = new QAction(MainWindow);
        actionStatistics_Page->setObjectName(QString::fromUtf8("actionStatistics_Page"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 798, 441));
        mainPage = new QWidget();
        mainPage->setObjectName(QString::fromUtf8("mainPage"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainPage->sizePolicy().hasHeightForWidth());
        mainPage->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(mainPage);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        widget = new QWidget(mainPage);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, -1, -1, 1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        RecipeSearchButton = new QPushButton(widget);
        RecipeSearchButton->setObjectName(QString::fromUtf8("RecipeSearchButton"));

        horizontalLayout->addWidget(RecipeSearchButton);

        IngredientSearchButton = new QPushButton(widget);
        IngredientSearchButton->setObjectName(QString::fromUtf8("IngredientSearchButton"));

        horizontalLayout->addWidget(IngredientSearchButton);

        StatisticsButton = new QPushButton(widget);
        StatisticsButton->setObjectName(QString::fromUtf8("StatisticsButton"));
        StatisticsButton->setEnabled(true);

        horizontalLayout->addWidget(StatisticsButton);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        labelWaitStatistics = new QLabel(widget);
        labelWaitStatistics->setObjectName(QString::fromUtf8("labelWaitStatistics"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelWaitStatistics->sizePolicy().hasHeightForWidth());
        labelWaitStatistics->setSizePolicy(sizePolicy1);
        labelWaitStatistics->setMinimumSize(QSize(0, 20));
        labelWaitStatistics->setMaximumSize(QSize(16777215, 25));
        labelWaitStatistics->setAlignment(Qt::AlignCenter);
        labelWaitStatistics->setWordWrap(false);

        gridLayout->addWidget(labelWaitStatistics, 2, 0, 1, 1);

        labelTitle = new QLabel(widget);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        sizePolicy1.setHeightForWidth(labelTitle->sizePolicy().hasHeightForWidth());
        labelTitle->setSizePolicy(sizePolicy1);
        labelTitle->setMaximumSize(QSize(16777215, 70));
        labelTitle->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelTitle, 0, 0, 1, 1);


        gridLayout_3->addWidget(widget, 0, 0, 1, 1);

        stackedWidget->addWidget(mainPage);
        recipeSearchPage = new QWidget();
        recipeSearchPage->setObjectName(QString::fromUtf8("recipeSearchPage"));
        gridLayout_5 = new QGridLayout(recipeSearchPage);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        ListWidgetIngredients = new QListWidget(recipeSearchPage);
        ListWidgetIngredients->setObjectName(QString::fromUtf8("ListWidgetIngredients"));
        ListWidgetIngredients->setMaximumSize(QSize(320, 16777215));
        ListWidgetIngredients->setWordWrap(true);

        gridLayout_5->addWidget(ListWidgetIngredients, 3, 2, 4, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        HomeButtonInRecipePage = new QPushButton(recipeSearchPage);
        HomeButtonInRecipePage->setObjectName(QString::fromUtf8("HomeButtonInRecipePage"));
        HomeButtonInRecipePage->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_6->addWidget(HomeButtonInRecipePage);

        LineEditSearchRecipe = new QLineEdit(recipeSearchPage);
        LineEditSearchRecipe->setObjectName(QString::fromUtf8("LineEditSearchRecipe"));

        horizontalLayout_6->addWidget(LineEditSearchRecipe);

        SearchButtonInRecipePage = new QPushButton(recipeSearchPage);
        SearchButtonInRecipePage->setObjectName(QString::fromUtf8("SearchButtonInRecipePage"));
        SearchButtonInRecipePage->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_6->addWidget(SearchButtonInRecipePage);


        gridLayout_5->addLayout(horizontalLayout_6, 1, 0, 1, 5);

        PreviousButton = new QPushButton(recipeSearchPage);
        PreviousButton->setObjectName(QString::fromUtf8("PreviousButton"));
        PreviousButton->setMaximumSize(QSize(180, 25));

        gridLayout_5->addWidget(PreviousButton, 6, 0, 1, 1);

        ListWidgetMatchingResult = new QListWidget(recipeSearchPage);
        ListWidgetMatchingResult->setObjectName(QString::fromUtf8("ListWidgetMatchingResult"));
        ListWidgetMatchingResult->setMinimumSize(QSize(0, 200));
        ListWidgetMatchingResult->setMaximumSize(QSize(360, 16777215));
        ListWidgetMatchingResult->setWordWrap(true);

        gridLayout_5->addWidget(ListWidgetMatchingResult, 3, 0, 2, 2);

        ListWidgetInstructions = new QListWidget(recipeSearchPage);
        ListWidgetInstructions->setObjectName(QString::fromUtf8("ListWidgetInstructions"));
        ListWidgetInstructions->setAutoScroll(true);
        ListWidgetInstructions->setWordWrap(true);

        gridLayout_5->addWidget(ListWidgetInstructions, 3, 3, 4, 2);

        NextButton = new QPushButton(recipeSearchPage);
        NextButton->setObjectName(QString::fromUtf8("NextButton"));
        NextButton->setMaximumSize(QSize(180, 25));

        gridLayout_5->addWidget(NextButton, 6, 1, 1, 1);

        ImageLabel = new QLabel(recipeSearchPage);
        ImageLabel->setObjectName(QString::fromUtf8("ImageLabel"));
        ImageLabel->setMaximumSize(QSize(360, 400));

        gridLayout_5->addWidget(ImageLabel, 5, 0, 1, 2);

        stackedWidget->addWidget(recipeSearchPage);
        ingredientSearchPage = new QWidget();
        ingredientSearchPage->setObjectName(QString::fromUtf8("ingredientSearchPage"));
        gridLayout_6 = new QGridLayout(ingredientSearchPage);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        LabelNumberRecipes = new QLabel(ingredientSearchPage);
        LabelNumberRecipes->setObjectName(QString::fromUtf8("LabelNumberRecipes"));

        gridLayout_6->addWidget(LabelNumberRecipes, 1, 2, 1, 2);

        ListWidgetRecipesContainingIngredient = new QListWidget(ingredientSearchPage);
        ListWidgetRecipesContainingIngredient->setObjectName(QString::fromUtf8("ListWidgetRecipesContainingIngredient"));
        ListWidgetRecipesContainingIngredient->setWordWrap(true);

        gridLayout_6->addWidget(ListWidgetRecipesContainingIngredient, 2, 2, 1, 2);

        ListWidgetStandardIngredients = new QListWidget(ingredientSearchPage);
        ListWidgetStandardIngredients->setObjectName(QString::fromUtf8("ListWidgetStandardIngredients"));
        ListWidgetStandardIngredients->setWordWrap(true);

        gridLayout_6->addWidget(ListWidgetStandardIngredients, 1, 0, 2, 2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        HomeButtonInIngredientPage = new QPushButton(ingredientSearchPage);
        HomeButtonInIngredientPage->setObjectName(QString::fromUtf8("HomeButtonInIngredientPage"));
        HomeButtonInIngredientPage->setMaximumSize(QSize(45, 30));

        horizontalLayout_7->addWidget(HomeButtonInIngredientPage);

        LineEditSearchIngredient = new QLineEdit(ingredientSearchPage);
        LineEditSearchIngredient->setObjectName(QString::fromUtf8("LineEditSearchIngredient"));

        horizontalLayout_7->addWidget(LineEditSearchIngredient);

        SearchButtonInIngredientPage = new QPushButton(ingredientSearchPage);
        SearchButtonInIngredientPage->setObjectName(QString::fromUtf8("SearchButtonInIngredientPage"));
        SearchButtonInIngredientPage->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_7->addWidget(SearchButtonInIngredientPage);


        gridLayout_6->addLayout(horizontalLayout_7, 0, 0, 1, 4);

        stackedWidget->addWidget(ingredientSearchPage);
        statisticsPage = new QWidget();
        statisticsPage->setObjectName(QString::fromUtf8("statisticsPage"));
        gridLayout_4 = new QGridLayout(statisticsPage);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        TopRecipesWithMoreIngredientsHistogram = new QChartView(statisticsPage);
        TopRecipesWithMoreIngredientsHistogram->setObjectName(QString::fromUtf8("TopRecipesWithMoreIngredientsHistogram"));

        gridLayout_4->addWidget(TopRecipesWithMoreIngredientsHistogram, 2, 2, 1, 1);

        RecipePartitionsPieChart = new QChartView(statisticsPage);
        RecipePartitionsPieChart->setObjectName(QString::fromUtf8("RecipePartitionsPieChart"));

        gridLayout_4->addWidget(RecipePartitionsPieChart, 2, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        HomeButtonInStatisticsPage = new QPushButton(statisticsPage);
        HomeButtonInStatisticsPage->setObjectName(QString::fromUtf8("HomeButtonInStatisticsPage"));
        HomeButtonInStatisticsPage->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_8->addWidget(HomeButtonInStatisticsPage);

        LineEditSearchNumberRecipesForIngredients = new QLineEdit(statisticsPage);
        LineEditSearchNumberRecipesForIngredients->setObjectName(QString::fromUtf8("LineEditSearchNumberRecipesForIngredients"));

        horizontalLayout_8->addWidget(LineEditSearchNumberRecipesForIngredients);

        SearchButtonInStatisticsPage = new QPushButton(statisticsPage);
        SearchButtonInStatisticsPage->setObjectName(QString::fromUtf8("SearchButtonInStatisticsPage"));
        SearchButtonInStatisticsPage->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_8->addWidget(SearchButtonInStatisticsPage);


        gridLayout_4->addLayout(horizontalLayout_8, 0, 0, 1, 3);

        RecipeWithImagesPieChart = new QChartView(statisticsPage);
        RecipeWithImagesPieChart->setObjectName(QString::fromUtf8("RecipeWithImagesPieChart"));

        gridLayout_4->addWidget(RecipeWithImagesPieChart, 1, 0, 1, 1);

        IngredientValidPieChart = new QChartView(statisticsPage);
        IngredientValidPieChart->setObjectName(QString::fromUtf8("IngredientValidPieChart"));

        gridLayout_4->addWidget(IngredientValidPieChart, 2, 1, 1, 1);

        TopRecipesWithMoreInstructionsHistogram = new QChartView(statisticsPage);
        TopRecipesWithMoreInstructionsHistogram->setObjectName(QString::fromUtf8("TopRecipesWithMoreInstructionsHistogram"));

        gridLayout_4->addWidget(TopRecipesWithMoreInstructionsHistogram, 1, 2, 1, 1);

        NumberRecipesForStdIngredientTable = new QTableWidget(statisticsPage);
        if (NumberRecipesForStdIngredientTable->columnCount() < 2)
            NumberRecipesForStdIngredientTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        NumberRecipesForStdIngredientTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        NumberRecipesForStdIngredientTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        NumberRecipesForStdIngredientTable->setObjectName(QString::fromUtf8("NumberRecipesForStdIngredientTable"));
        NumberRecipesForStdIngredientTable->horizontalHeader()->setDefaultSectionSize(130);
        NumberRecipesForStdIngredientTable->horizontalHeader()->setStretchLastSection(true);
        NumberRecipesForStdIngredientTable->verticalHeader()->setStretchLastSection(false);

        gridLayout_4->addWidget(NumberRecipesForStdIngredientTable, 1, 1, 1, 1);

        stackedWidget->addWidget(statisticsPage);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 831, 22));
        menuRecipe1M = new QMenu(menuBar);
        menuRecipe1M->setObjectName(QString::fromUtf8("menuRecipe1M"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuRecipe1M->menuAction());
        menuRecipe1M->addAction(actionRecipe_Search_Page);
        menuRecipe1M->addAction(actionIngredient_Search_Page);
        menuRecipe1M->addAction(actionStatistics_Page);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Recipe1M", nullptr));
        actionRecipe_Search_Page->setText(QApplication::translate("MainWindow", "Recipe Search Page", nullptr));
        actionIngredient_Search_Page->setText(QApplication::translate("MainWindow", "Ingredient Search Page", nullptr));
        actionStatistics_Page->setText(QApplication::translate("MainWindow", "Statistics Page", nullptr));
        RecipeSearchButton->setText(QApplication::translate("MainWindow", "Recipe Search", nullptr));
        IngredientSearchButton->setText(QApplication::translate("MainWindow", "Ingredient Search", nullptr));
        StatisticsButton->setText(QApplication::translate("MainWindow", "Statistics", nullptr));
        labelWaitStatistics->setText(QString());
        labelTitle->setText(QApplication::translate("MainWindow", "Recipe1M:\n"
"Recipes and ingredients search", nullptr));
        HomeButtonInRecipePage->setText(QApplication::translate("MainWindow", "Home", nullptr));
        SearchButtonInRecipePage->setText(QApplication::translate("MainWindow", "Search", nullptr));
        PreviousButton->setText(QApplication::translate("MainWindow", "Previous", nullptr));
        NextButton->setText(QApplication::translate("MainWindow", "Next", nullptr));
        ImageLabel->setText(QString());
        LabelNumberRecipes->setText(QApplication::translate("MainWindow", "Total numbers of recipes containing the ingredient: ", nullptr));
        HomeButtonInIngredientPage->setText(QApplication::translate("MainWindow", "Home", nullptr));
        SearchButtonInIngredientPage->setText(QApplication::translate("MainWindow", "Search", nullptr));
        HomeButtonInStatisticsPage->setText(QApplication::translate("MainWindow", "Home", nullptr));
        SearchButtonInStatisticsPage->setText(QApplication::translate("MainWindow", "Search", nullptr));
        QTableWidgetItem *___qtablewidgetitem = NumberRecipesForStdIngredientTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Ingredient", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = NumberRecipesForStdIngredientTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Number of recipes", nullptr));
        menuRecipe1M->setTitle(QApplication::translate("MainWindow", "Pages", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
