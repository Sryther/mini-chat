#include "application.h"
#include <exception>
#include <stdexcept>
#include <QMessageBox>
#include <QObject>
#include <QEvent>
#include <QApplication>

/**
 * @brief Application::Application
 * @param argc
 * @param argv
 */
Application::Application(int& argc, char** argv) :
  QApplication(argc, argv) {}

/**
 * @brief Application::notify
 * @param receiver
 * @param event
 * @return
 */
bool Application::notify(QObject* receiver, QEvent* event) {
  bool done = true;
  try {
    done = QApplication::notify(receiver, event);
  } catch (const std::exception& ex) {
      QMessageBox* box = new QMessageBox();
      box->critical(NULL, "Critical error", ex.what());
      delete box;
      box = nullptr;
  } catch (...) {
      QMessageBox* box = new QMessageBox();
      box->critical(NULL, "Critical error", "Unknown error");
      delete box;
      box = nullptr;
  }
  return done;
}
