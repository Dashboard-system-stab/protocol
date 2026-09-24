#ifndef SIGNAL_TREE_H
#define SIGNAL_TREE_H

#include <cstring>
#include <string>
#include <QTextCodec>
#include <QString>
#include <QByteArray>

#include "treenode.h"
#include "mjutils.h"
#include "mj_mon_spec.h"

TreeNode * create_mon_in_tree(mj_mon_t * mj);
TreeNode * create_mon_out_tree(mj_mon_t * mj);
TreeNode * create_mon_params_tree(mj_mon_t * mj);

#endif /* SIGNAL_TREE_H */