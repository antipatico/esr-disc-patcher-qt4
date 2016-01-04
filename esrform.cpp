/*
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA  02110-1301, USA.

    ---
    Copyright (C) 2008, Tatsh
 */

#include <QtGui>
#include "esrform.h"
#include <iostream>

ESRForm::ESRForm(QWidget *parent) : QWidget(parent) {
  setupUi(this);
}

void ESRForm::on_buttonPatch_clicked() {
#ifdef __DEBUG__
  std::cout << "Patch clicked." << std::endl;
#endif

  QString image = QFileDialog::getOpenFileName(this,
                    tr("Select disc image to patch"),
                    QDir::currentPath(),
                    tr("All supported image types (*.iso *.bin);;ISO files (*.iso);;BIN files (*.bin)"));

  if (!image.isEmpty()) { // Did we get an image?
#ifdef __DEBUG__
    std::cout << "Got " << image.toUtf8().constData() << "." << std::endl;
#endif

    const char *file = image.toLatin1().data();
    
    switch (m_patcher.doPatch((char*)file)) {
      case ESR_FILE_OK:
        QMessageBox::information(this, tr("Notification"), tr("Successfully patched %1.").arg(image));
        break;

      case ESR_FILE_ALREADY_PATCHED:
        QMessageBox::information(this, tr("Notification"), tr("%1 is already patched.").arg(image));
        break;

      case ESR_FILE_CANNOT_OPEN:
        QMessageBox::critical(this, tr("Error"), tr("Could not open %1.").arg(image));
        break;

      case ESR_FILE_NO_UDF_DESCRIPTOR:
        QMessageBox::critical(this, tr("Error"), tr("No UDF descriptor found in %1.").arg(image));
        break;

      default:
        QMessageBox::critical(this, tr("Error"), tr("Unknown error during patching procedure."));
        break;
    }
  }
#ifdef __DEBUG__
  else
    std::cout << "No disc image selected for patching." << std::endl;
#endif

  return;
}

void ESRForm::on_buttonUnpatch_clicked() {
#ifdef __DEBUG__
  std::cout << "Unpatch clicked." << std::endl;
#endif

  QString image = QFileDialog::getOpenFileName(this,
                    tr("Select disc image to unpatch"),
                    QDir::currentPath(),
                    tr("All supported image types (*.iso *.bin);;ISO files (*.iso);;BIN files (*.bin)"));

  if (!image.isEmpty()) {
#ifdef __DEBUG__
    std::cout << "Got " << image.toUtf8().constData() << "." << std::endl;
#endif
    
    const char *file = image.toLatin1().data();
    
    switch (m_patcher.doUnPatch((char*)file)) {
      case ESR_FILE_OK:
        QMessageBox::information(this, tr("Notification"), tr("Successfully unpatched %1.").arg(image));
        break;

      case ESR_FILE_NOT_PATCHED:
        QMessageBox::information(this, tr("Notification"), tr("%1 is not patched.").arg(image));
        break;

      case ESR_FILE_CANNOT_OPEN:
        QMessageBox::critical(this, tr("Error"), tr("Could not open %1.").arg(image));
        break;

      case ESR_FILE_NO_UDF_DESCRIPTOR:
        QMessageBox::critical(this, tr("Error"), tr("No UDF descriptor found in %1.").arg(image));
        break;

      default:
        QMessageBox::critical(this, tr("Error"), tr("Unknown error during unpatching procedure."));
        break;
    }
  }
#ifdef __DEBUG__
  else
    std::cout << "No disc image selected for unpatching." << std::endl;
#endif

  return;
}
