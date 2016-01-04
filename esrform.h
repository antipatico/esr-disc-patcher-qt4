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

#ifndef ESRFORM_H
#define ESRFORM_H

#include "ui_esrform.h"

#include "Patcher.h"

class ESRForm : public QWidget, private Ui::ESRForm {
  Q_OBJECT
      
  public:
    ESRForm(QWidget *parent = 0);
    
  private:
    CPatcher m_patcher;
    
  private slots:
    void on_buttonPatch_clicked();
    void on_buttonUnpatch_clicked();
};

#endif
