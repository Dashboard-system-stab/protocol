#ifndef SIGNAL_TREE_H
#define SIGNAL_TREE_H

#include <cstring>
#include <string>
#include <QTextCodec>
#include <QString>
#include <QByteArray>

#include "treenode.h"
#include "mjutils.h"
#include "mj_wp_imu_spec.h"

TreeNode * create_wp_imu_in_tree(mj_wp_imu_t * mj);
TreeNode * create_wp_imu_out_tree(mj_wp_imu_t * mj);
TreeNode * create_wp_imu_params_tree(mj_wp_imu_t * mj);

#endif /* SIGNAL_TREE_H */