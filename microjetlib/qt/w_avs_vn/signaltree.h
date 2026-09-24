#ifndef SIGNAL_TREE_H
#define SIGNAL_TREE_H

#include <cstring>
#include <string>
#include <QTextCodec>
#include <QString>
#include <QByteArray>

#include "treenode.h"
#include "mjutils.h"
#include "mj_w_avs_vn_spec.h"

TreeNode * create_w_avs_vn_in_tree(mj_w_avs_vn_t * mj);
TreeNode * create_w_avs_vn_out_tree(mj_w_avs_vn_t * mj);
TreeNode * create_w_avs_vn_params_tree(mj_w_avs_vn_t * mj);

#endif /* SIGNAL_TREE_H */