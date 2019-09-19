#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QFormLayout>
#include <QVBoxLayout>

class AboutWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AboutWindow(QWidget *parent = nullptr);
    ~AboutWindow();

private:
    //===============Form elements===============//
    //================First Group================//
    QGroupBox* programInfoGroupBox;              //
    QLabel* programNameLabel;                    //
    QLabel* programName;                         //
    QLabel* versionLabel;                        //
    QLabel* version;                             //
    QLabel* publishingDateLabel;                 //
    QLabel* publishingDate;                      //
    QLabel* lastChangeDateLabel;                 //
    QLabel* lastChangeDate;                      //
    QFormLayout* programInfoFormLayout;          //
    //===========================================//
    //===============Second Group================//
    QGroupBox* organizationInfoGroupBox;         //
    QLabel* officialNameLabel;                   //
    QLabel* officialName;                        //
    QLabel* webSiteLabel;                        //
    QLabel* webSite;                             //
    QLabel* departmentLabel;                     //
    QLabel* department;                          //
    QLabel* majorLabel;                          //
    QLabel* major;                               //
    QFormLayout* organizationInfoFormLayout;     //
    //===========================================//
    //===============Third Group=================//
    QGroupBox* locationInfoGroupBox;             //
    QLabel* countryLabel;                        //
    QLabel* country;                             //
    QLabel* cityLabel;                           //
    QLabel* city;                                //
    QFormLayout* locationInfoFormLayout;         //
    //===========================================//
    //===============Fourth Group================//
    QGroupBox* authorInfoGroupBox;               //
    QLabel* lastNameLabel;                       //
    QLabel* lastName;                            //
    QLabel* firstNameLabel;                      //
    QLabel* firstName;                           //
    QLabel* patronymicLabel;                     //
    QLabel* patronymic;                          //
    QLabel* firstEmailLabel;                     //
    QLabel* firstEmail;                          //
    QLabel* secondEmailLabel;                    //
    QLabel* secondEmail;                         //
    QLabel* thirdEmailLabel;                     //
    QLabel* thirdEmail;                          //
    QLabel* fourthEmailLabel;                    //
    QLabel* fourthEmail;                         //
    QLabel* githubLabel;                         //
    QLabel* github;                              //
    QLabel* linkedinLabel;                       //
    QLabel* linkedin;                            //
    QFormLayout* authorInfoFormLayout;           //
    //===========================================//
    //================Main Layout================//
    QVBoxLayout* mainLayout;                     //
    //===========================================//
};

#endif // ABOUTWINDOW_H
