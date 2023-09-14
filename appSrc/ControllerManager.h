/******************************************************************************
 * Copyright 2023-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file          ControllerManager.h
 * @brief
 * @Description   控制器
 * @author        liukuan<807874484@qq.com>
 * @date          2023/09/14
 * @history
 *****************************************************************************/
#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H


#include <QObject>

class ControllerManager : public QObject
{
    Q_OBJECT
public:
    explicit ControllerManager(QObject *parent = nullptr);




signals:

};

#endif // CONTROLLERMANAGER_H
