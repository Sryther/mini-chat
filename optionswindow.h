#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <QFrame>
#include <QLineEdit>
#include <QColorDialog>
#include <QColor>

namespace Ui {
class OptionsWindow;
}

class OptionsWindow : public QFrame
{
    Q_OBJECT

public:
    explicit OptionsWindow(QWidget *parent = 0, QLineEdit *placeholder = nullptr);
    OptionsWindow(const OptionsWindow &&other);
    OptionsWindow(const OptionsWindow &other);
    void updateFields();
    ~OptionsWindow();

private slots:
    void on_loadButton_clicked();
    void on_saveButton_clicked();
    void on_pushButton_clicked();

private:
    Ui::OptionsWindow *ui;
    QLineEdit* usernamePlaceholder;
    QString convertColor(QColor color);
    QColor convertColor(QString color);
    QString _newColor;
};

#endif // OPTIONSWINDOW_H
