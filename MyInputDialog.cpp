#include "MyInputDialog.h"

MyInputDialog::MyInputDialog(QWidget *parent, int height, int width) : QDialog(parent){
    this->setAttribute(Qt::WA_QuitOnClose, false);
    vbox = new QVBoxLayout;
    textValue = new QLineEdit();
    this->resize(height, width);
    this->setFont(QFont("Arial", 20, 1, false));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    vbox->addWidget(buttonBox);
    this->setLayout(vbox);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

QString MyInputDialog::getText(QString profileName,  bool* okayPressed){
    this->setWindowTitle("Saving...");
    auto promptText = new QLabel(tr("Please tell me your name!"));
    promptText->setAlignment(Qt::AlignCenter);
    vbox->insertWidget(0, promptText);
    this->textValue->setText(profileName);

    textValue->setPlaceholderText(profileName);
    vbox->insertWidget(1, textValue);

    if(this->exec() == QDialog::Accepted){
        *okayPressed = true;
        return this->textValue->text();
    }else{
        return profileName;
    }


}

QString MyInputDialog::updateText(QString profileName,  bool* okayPressed){
    this->setWindowTitle("Saving...");
    QString labelText = "Hello " + profileName + "! Not you? Would you like to update your name? Press OK to change or keep your name.";
    auto promptText = new QLabel(labelText);
    promptText->setAlignment(Qt::AlignCenter);
    vbox->insertWidget(0, promptText);
    this->textValue->setText(profileName);

    textValue->setPlaceholderText(profileName);
    vbox->insertWidget(1, textValue);

    if(this->exec() == QDialog::Accepted){
        *okayPressed = true;
        return this->textValue->text();
    }else{
        return profileName;
    }

    return this->textValue->text();
}

void MyInputDialog::keyPressEvent(QKeyEvent *e){
    if (e->key() == Qt::Key_Enter){
        qDebug() << "Enter pressed";
        this->exec();
    }else{
        QDialog::keyPressEvent(e);
    }
}

