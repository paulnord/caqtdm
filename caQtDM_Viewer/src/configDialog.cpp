/*
 *  This file is part of the caQtDM Framework, developed at the Paul Scherrer Institut,
 *  Villigen, Switzerland
 *
 *  The caQtDM Framework is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  The caQtDM Framework is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with the caQtDM Framework.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Copyright (c) 2010 - 2014
 *
 *  Author:
 *    Anton Mezger
 *  Contact details:
 *    anton.mezger@psi.ch
 */

#include "configDialog.h"
#include "qstandardpaths.h"

configDialog::configDialog(const bool debugWindow, const QList<QString> &urls, const QList<QString> &files, QWidget *parent): QWidget(parent)
{
    int thisWidth = 600;
    int thisHeight = 500;
    Qt::WindowFlags flags = Qt::Dialog;
    setWindowFlags(flags);
    setWindowModality (Qt::WindowModal);
    //setPalette(Qt::transparent);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter, QSize(thisWidth,thisHeight), qApp->desktop()->availableGeometry()));

    ClearConfigButtonClicked = false;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    setWindowTitle("caQtDM tablet configuration");
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    mainLayout->addWidget(new QLabel("<h1>Configuration data</h1>"), 0, Qt::AlignCenter);

    QGridLayout *clearLayout = new QGridLayout;
    QGroupBox* clearBox = new QGroupBox("Local ui/prc files");

    QString str= QString::number((int) NumberOfFiles());
    QLabel *label = new QLabel("Number:");
    fileCountLabel = new QLabel(str);
    clearLayout->addWidget(label, 0, 0);
    clearLayout->addWidget(fileCountLabel, 0, 1);

    QPushButton* clearConfigButton = new QPushButton("Clear config files");
    clearLayout->addWidget(clearConfigButton, 0, 2);
    connect(clearConfigButton, SIGNAL(clicked()), this, SLOT(clearConfigClicked()) );

    QPushButton* clearUiButton = new QPushButton("Clear ui files");
    clearLayout->addWidget(clearUiButton, 0, 3);
    connect(clearUiButton, SIGNAL(clicked()), this, SLOT(clearUiClicked()) );

    QLabel *debugLabel = new QLabel("   ");
    clearLayout->addWidget(debugLabel, 0, 4);

    debugCheckBox = new QCheckBox("Debug window");
    debugCheckBox->setChecked(debugWindow);
    clearLayout->addWidget(debugCheckBox, 0, 5);

    clearBox->setLayout(clearLayout);
    mainLayout->addWidget(clearBox);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Horizontal );
    //connect(box, SIGNAL(rejected()), this, SLOT(reject()));
    //connect(box, SIGNAL(accepted()), this, SLOT(accept()));

    QGridLayout* urlLayout = new QGridLayout;
    QGroupBox* urlBox = new QGroupBox("Choose your url where your config file is located");
    for(int i=0; i< 5; i++) {
           urlEdit[i] = new QLineEdit();
           if(i< urls.length())  urlEdit[i]->setText(urls.at(i));
           urlLayout->addWidget(urlEdit[i], i, 0);
           urlRadio[i] = new QRadioButton();
           urlLayout->addWidget(urlRadio[i], i, 1);
    }
    urlRadio[0]->setChecked(true);
    urlBox->setLayout(urlLayout);
    mainLayout->addWidget(urlBox);

    QGridLayout* fileLayout = new QGridLayout;
    QGroupBox* fileBox = new QGroupBox("Choose your config file at the above url");

    for(int i=0; i< 5; i++) {
           fileEdit[i] = new QLineEdit();
           if(i< files.length())  fileEdit[i]->setText(files.at(i));
           fileLayout->addWidget(fileEdit[i], i, 0);
           fileRadio[i] = new QRadioButton();
           fileLayout->addWidget(fileRadio[i], i, 1);
    }
    fileRadio[0]->setChecked(true);
    fileBox->setLayout(fileLayout);
    mainLayout->addWidget(fileBox);

    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
    showNormal();
}

void configDialog::getChoice(QString &url, QString &file, QList<QString> &urls, QList<QString> &files, bool &debugWindow)
{
    urls.clear();
    files.clear();

    for(int i=0; i< 5; i++) {
        urls.append(urlEdit[i]->text());
        if(urlRadio[i]->isChecked()) {
            url = urlEdit[i]->text();
        }
    }
    for(int i=0; i< 5; i++) {
        files.append(fileEdit[i]->text());
        if(fileRadio[i]->isChecked()) {
            file = fileEdit[i]->text();
        }
    }
    debugWindow = debugCheckBox->isChecked();
}

void configDialog::clearUiClicked()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    path.append("/");
    QDir dir(path);
    dir.setNameFilters(QStringList() << "*.ui" << "*.prc");
    dir.setFilter(QDir::Files);
    foreach(QString dirFile, dir.entryList()) dir.remove(dirFile);

    QString str= QString::number((int) NumberOfFiles());
    fileCountLabel->setText(str);
}

void configDialog::clearConfigClicked()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    path.append("/");
    QDir dir(path);
    dir.setNameFilters(QStringList() << "*.config" << "*.xml");
    dir.setFilter(QDir::Files);
    foreach(QString dirFile, dir.entryList()) dir.remove(dirFile);
    ClearConfigButtonClicked = true;
    close();
}

bool configDialog::isClearConfig()
{
    return ClearConfigButtonClicked;
}

int configDialog::NumberOfFiles()
{
    int count = 0;
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    path.append("/");
    QDir dir(path);
    dir.setNameFilters(QStringList() << "*.ui" << "*.prc");
    dir.setFilter(QDir::Files);
    foreach(QString dirFile, dir.entryList()) count++;
    return count;
}

void configDialog::exec()
{
    connect(buttonBox, SIGNAL(rejected()), &loop, SLOT(quit()) );
    connect(buttonBox, SIGNAL(accepted()), &loop, SLOT(quit()) );
    loop.exec();
    close();
}

void configDialog::closeEvent(QCloseEvent *event)
{
    loop.quit();
}
