#ifndef SIGNAL_TREE_H
#define SIGNAL_TREE_H

#include <cstring>
#include <string>
#include <QTextCodec>
#include <QString>
#include <QByteArray>

#include "treenode.h"
#include "mjutils.h"
#include "mj_imu_sensor_spec.h"

TreeNode * create_imu_sensor_in_tree(mj_imu_sensor_t * mj);
TreeNode * create_imu_sensor_out_tree(mj_imu_sensor_t * mj);
TreeNode * create_imu_sensor_params_tree(mj_imu_sensor_t * mj);

#endif /* SIGNAL_TREE_H */