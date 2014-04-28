#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <QFrame>
#include <QLineEdit>

namespace Ui {
class OptionsWindow;
}

class OptionsWindow : public QFrame
{
    Q_OBJECT

public:
    explicit OptionsWindow(QWidget *parent = 0, QLineEdit *placeholder = nullptr);
    ~OptionsWindow();

private slots:
    void on_loadButton_clicked();

    void on_saveButton_clicked();

    void on_usernameField_textChanged(const QString &arg1);

    void on_portField_textChanged(const QString &arg1);

private:
    Ui::OptionsWindow *ui;
    void updateFields();
    QLineEdit* usernamePlaceholder;
};

#endif // OPTIONSWINDOW_H
