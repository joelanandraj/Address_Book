#include "contact.h"
#include "qtaddcontactdialog.h"
#include <QDialog>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <Qtwidgets/QPushButton>
#include <QMessageBox>

QtAddContactDialog::QtAddContactDialog(Contact &c, QWidget *parent, Qt::WindowFlags f) :
            QDialog(parent, f), contactForm(new QtContactForm()), outContact(c)
{
    QVBoxLayout *mainContainer = new QVBoxLayout();
    mainContainer->addLayout(contactForm);

    QHBoxLayout *buttonContainer = new QHBoxLayout();
    QPushButton *addButton = new QPushButton("Add");
    QPushButton *cancelButton = new QPushButton("Cancel");
    
    buttonContainer->addWidget(addButton);
    buttonContainer->addWidget(cancelButton);
    mainContainer->addLayout(buttonContainer);

    connect(addButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    setLayout(mainContainer);
    setWindowTitle("New Contact");
}

void QtAddContactDialog::accept()
{
    outContact.firstName = contactForm->firstNameField->text().toStdString();
    outContact.lastName = contactForm->lastNameField->text().toStdString();
    outContact.address = contactForm->addressField->text().toStdString();
    outContact.phoneNumber = contactForm->phoneNumberField->text().toStdString();
    QString str=contactForm->phoneNumberField->text();
    outContact.email = contactForm->emailField->text().toStdString();
    QString email1 = contactForm->emailField->text();

    QMessageBox msbx;
    QRegExp re("\\d*"); // a digit (\d), zero or more times (*)
    //EMail Validation
    QRegExp mailchk("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailchk.setCaseSensitivity(Qt::CaseInsensitive);
    mailchk.setPatternSyntax(QRegExp::RegExp);

    if(str.length()>10 ||str.length()<10 )
    {
    msbx.setText("Invalid Phone Number");
    msbx.exec();
    }
    else if (!re.exactMatch(str))
    {

          msbx.setText("Invalid Phone Number");
    msbx.exec();
    }
    else if(!mailchk.exactMatch(email1))
    {

        msbx.setText("Invalid Email");
        msbx.exec();
    }

    else
    {
    QDialog::accept();
    }
}
