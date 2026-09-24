#ifndef SIGNAL_TREE_H
#define SIGNAL_TREE_H

#include <cstring>
#include <string>
#include <QTextCodec>
#include <QString>
#include <QByteArray>

#include "treenode.h"
#include "mjutils.h"
#include "mj_trg_spec.h"

TreeNode * create_trg_in_tree(mj_trg_t * mj);
TreeNode * create_trg_out_tree(mj_trg_t * mj);
TreeNode * create_trg_params_tree(mj_trg_t * mj);

#endif /* SIGNAL_TREE_H */