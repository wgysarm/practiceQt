#include "TestUI.h"
#include <QDebug>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>


TestUI::TestUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QListWidgetItem *item1 = new QListWidgetItem(tr("item1"), ui.listWidget);

	QListWidgetItem *item2 = new QListWidgetItem();
	item2->setText(tr("item2"));
	ui.listWidget->insertItem(2, item2);
	ui.tableWidget->setColumnCount(5);
	ui.tableWidget->setRowCount(6);
	ui.tableWidget->setItem(0, 0 ,new QTableWidgetItem(tr("table item00")) );
	
	ui.treeWidget->setColumnCount(2);
	ui.treeWidget->setHeaderLabel(tr("image"));
	QList<QTreeWidgetItem *>treeItemList;
	//for(int i = 0; i < 10 ; i++)
	//{
	//	treeItemList.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
	//}
	//ui.treeWidget->insertTopLevelItems(0, treeItemList);
	treeItem1 = new QTreeWidgetItem(ui.treeWidget,QStringList(tr("image1")));

	QTreeWidgetItem *treeItem1_1 = new QTreeWidgetItem(treeItem1, QStringList(tr("image1_1")));
	treeItem1->addChild(treeItem1_1);
	treeItem2 = new QTreeWidgetItem(ui.treeWidget, QStringList(tr("image2")));

	QTreeWidgetItem *treeItem2_1 = new QTreeWidgetItem(treeItem2, QStringList(tr("image2_!")));
	treeItem2->addChild(treeItem2_1);
	treeItem1->setExpanded(true);
	treeItem2->setExpanded(true);


	QWidget *tab3 = new QWidget(this);

	//tab3->setWindowTitle("tab3");
	//uiH.setupUi(tab3);
	QHBoxLayout *hLayout = new QHBoxLayout(tab3);
	QPushButton *pbAddTab = new QPushButton("add", tab3);
	QPushButton *pbDelTab = new QPushButton("del", tab3);
	labelTab3 = new QLabel("tab3label",this);

	hLayout->addWidget(pbAddTab);
	hLayout->addWidget(pbDelTab);
	hLayout->addWidget(labelTab3);
	tab3->setLayout(hLayout);


	ui.tabWidget->addTab(tab3,"tab31");



	QLabel *lab = new QLabel(this);
	lab->setText("what");
	ui.tabWidget->addTab(lab, "label");
	
	//ui.tabWidget->removeTab(0);


	QObject::connect(ui.treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(SlotPrint(QTreeWidgetItem*, int)));
	QObject::connect(ui.treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(SlotPrint(QTreeWidgetItem*, int)));

	QObject::connect(ui.listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SlotPrintListWidget(QListWidgetItem*)));
	QObject::connect(pbAddTab, &QPushButton::clicked, [&](){qDebug() << "add"; labelTab3->setText("jjj"); 	QWidget *tab4 = new QWidget(this);	ui.tabWidget->addTab(tab4,"tab4");});
	QObject::connect(pbAddTab, &QPushButton::clicked, [&](){qDebug() << "del";});

	//QObject::connect(item1, SIGNAL(), this, SLOT(SlotPrint1()));


}

TestUI::~TestUI()
{

}



void TestUI::SlotPrint(QTreeWidgetItem *item, int column)
{

	QTreeWidgetItem *parent = item->parent();
	if(NULL==parent) //注意：最顶端项是没有父节点的，双击这些项时注意(陷阱)
	return;
	int col = parent->indexOfChild(item); //item在父项中的节点行号(从0开始)

	qDebug() << item->text(column) << "" << column;

	if(0==col) //Band1
	{
		qDebug() << "clicked1!";
		//执行对应操作
	}
	if(1==col) //Band2
	{
		qDebug() << "clicked2!";
     //执行对应操作
	}


}


void TestUI::SlotPrint1()
{
	qDebug() << "clicked1";
}

void TestUI::SlotPrintListWidget(QListWidgetItem *item)
{
	qDebug() << "clicked;";
	qDebug() << item->text();
	qDebug() << ui.listWidget->currentRow();


}

