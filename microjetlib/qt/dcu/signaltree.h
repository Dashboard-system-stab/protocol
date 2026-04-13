#ifndef SIGNAL_TREE_H
#define SIGNAL_TREE_H

#include <cstring>
#include <string>
#include <QTextCodec>
#include <QString>
#include <QByteArray>

#include "treenode.h"
#include "mjutils.h"
#include "mj_dcu_spec.h"

TreeNode * create_dcu_in_tree(mj_dcu_t * mj);
TreeNode * create_dcu_out_tree(mj_dcu_t * mj);
TreeNode * create_dcu_params_tree(mj_dcu_t * mj);

#endif /* SIGNAL_TREE_H */