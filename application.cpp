#include "application.h"
#include <exception>
#include <stdexcept>
#include <QMessageBox>
#include <QObject>
#include <QEvent>
#include <QApplication>

Application::Application(int& argc, char** argv) :
  QApplication(argc, argv) {}

bool Application::notify(QObject* receiver, QEvent* event) {
  bool done = true;
  try {
    done = QApplication::notify(receiver, event);
  } catch (const std::exception& ex) {
      QMessageBox* box = new QMessageBox();
      box->critical(NULL, "Critical error", ex.what());
      box = nullptr;
  } catch (...) {
      QMessageBox* box = new QMessageBox();
      box->critical(NULL, "Critical error", "Unknown error");
  }
  return done;
}
