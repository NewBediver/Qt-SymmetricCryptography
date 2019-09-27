#include "aboutwindow.h"

#include <QDate>
#include <QDateTime>

AboutWindow::AboutWindow(QWidget *parent) : QWidget(parent)
{
    // Create ProgramInfoGroupBox and fill it
    programInfoGroupBox = new QGroupBox("Program information");

    programNameLabel = new QLabel("Program name:");
    programName = new QLabel("Symmetric cryptography");
    versionLabel = new QLabel("Version:");
    version = new QLabel("0.15");
    publishingDateLabel = new QLabel("Publishing date:");
    publishingDate = new QLabel(QDateTime(QDate(2019, 9, 14)).date().toString());
    lastChangeDateLabel = new QLabel("Latest changes:");
    lastChangeDate = new QLabel(QDateTime(QDate(2019, 9, 27)).date().toString());

    programInfoFormLayout = new QFormLayout();
    programInfoFormLayout->addRow(programNameLabel, programName);
    programInfoFormLayout->addRow(versionLabel, version);
    programInfoFormLayout->addRow(publishingDateLabel, publishingDate);
    programInfoFormLayout->addRow(lastChangeDateLabel, lastChangeDate);
    programInfoFormLayout->setHorizontalSpacing(31);

    programInfoGroupBox->setLayout(programInfoFormLayout);

    // Create OrganizationInfoGroupBox and fill it
    organizationInfoGroupBox = new QGroupBox("Organization information");

    officialNameLabel = new QLabel("Official name:");
    officialName = new QLabel("Komsomolsk-on-Amur State University (KnASU)");
    webSiteLabel = new QLabel("Official Web-site:");
    webSite = new QLabel("https://knastu.ru/");
    departmentLabel = new QLabel("Department:");
    department = new QLabel("Department of computer technologies");
    majorLabel = new QLabel("Major:");
    major = new QLabel("Information security of automated systems");

    organizationInfoFormLayout = new QFormLayout();
    organizationInfoFormLayout->addRow(officialNameLabel, officialName);
    organizationInfoFormLayout->addRow(webSiteLabel, webSite);
    organizationInfoFormLayout->addRow(departmentLabel, department);
    organizationInfoFormLayout->addRow(majorLabel, major);
    organizationInfoFormLayout->setHorizontalSpacing(25);

    organizationInfoGroupBox->setLayout(organizationInfoFormLayout);

    // Create LocationInfoGroupBox and fill it
    locationInfoGroupBox = new QGroupBox("Location information");

    countryLabel = new QLabel("Country:");
    country = new QLabel("Russia");
    cityLabel = new QLabel("City:");
    city = new QLabel("Komsomolsk-on-Amur");

    locationInfoFormLayout = new QFormLayout();
    locationInfoFormLayout->addRow(countryLabel, country);
    locationInfoFormLayout->addRow(cityLabel, city);
    locationInfoFormLayout->setHorizontalSpacing(65);

    locationInfoGroupBox->setLayout(locationInfoFormLayout);

    // Create AuthorInfoGroupBox and fill it
    authorInfoGroupBox = new QGroupBox("Author information");

    lastNameLabel = new QLabel("Last name:");
    lastName = new QLabel("Serikov");
    firstNameLabel = new QLabel("Frist name:");
    firstName = new QLabel("Vladislav");
    patronymicLabel = new QLabel("Patronomyc:");
    patronymic = new QLabel("Aleksandrovich");
    firstEmailLabel = new QLabel("First e-mail:");
    firstEmail = new QLabel("serikov_v1999@mail.ru");
    secondEmailLabel = new QLabel("Second e-mail:");
    secondEmail = new QLabel("SerikovVA@outlook.com");
    thirdEmailLabel = new QLabel("Third e-mail:");
    thirdEmail = new QLabel("SerikovVA1999@gmail.com");
    fourthEmailLabel = new QLabel("Fourth e-mail:");
    fourthEmail = new QLabel("Bedivar@yandex.ru");
    githubLabel = new QLabel("GitHub:");
    github = new QLabel("https://github.com/NewBediver");
    linkedinLabel = new QLabel("LinkedIn:");
    linkedin = new QLabel("https://www.linkedin.com/in/vladislav-serikov-29391b170/");

    authorInfoFormLayout = new QFormLayout();
    authorInfoFormLayout->addRow(lastNameLabel, lastName);
    authorInfoFormLayout->addRow(firstNameLabel, firstName);
    authorInfoFormLayout->addRow(patronymicLabel, patronymic);
    authorInfoFormLayout->addRow(firstEmailLabel, firstEmail);
    authorInfoFormLayout->addRow(secondEmailLabel, secondEmail);
    authorInfoFormLayout->addRow(thirdEmailLabel, thirdEmail);
    authorInfoFormLayout->addRow(fourthEmailLabel, fourthEmail);
    authorInfoFormLayout->addRow(githubLabel, github);
    authorInfoFormLayout->addRow(linkedinLabel, linkedin);
    authorInfoFormLayout->setHorizontalSpacing(38);

    authorInfoGroupBox->setLayout(authorInfoFormLayout);

    // Create MainLayout and fill it with grop boxes
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(programInfoGroupBox);
    mainLayout->addWidget(organizationInfoGroupBox);
    mainLayout->addWidget(locationInfoGroupBox);
    mainLayout->addWidget(authorInfoGroupBox);
}

AboutWindow::~AboutWindow()
{
    delete programNameLabel;
    delete programName;
    delete versionLabel;
    delete version;
    delete publishingDateLabel;
    delete publishingDate;
    delete lastChangeDateLabel;
    delete lastChangeDate;
    delete programInfoFormLayout;
    delete programInfoGroupBox;

    delete officialNameLabel;
    delete officialName;
    delete webSiteLabel;
    delete webSite;
    delete departmentLabel;
    delete department;
    delete majorLabel;
    delete major;
    delete organizationInfoFormLayout;
    delete organizationInfoGroupBox;

    delete countryLabel;
    delete country;
    delete cityLabel;
    delete city;
    delete locationInfoFormLayout;
    delete locationInfoGroupBox;

    delete lastNameLabel;
    delete lastName;
    delete firstNameLabel;
    delete firstName;
    delete patronymicLabel;
    delete patronymic;
    delete firstEmailLabel;
    delete firstEmail;
    delete secondEmailLabel;
    delete secondEmail;
    delete thirdEmailLabel;
    delete thirdEmail;
    delete fourthEmailLabel;
    delete fourthEmail;
    delete githubLabel;
    delete github;
    delete linkedinLabel;
    delete linkedin;
    delete authorInfoFormLayout;
    delete authorInfoGroupBox;

    delete mainLayout;
}
