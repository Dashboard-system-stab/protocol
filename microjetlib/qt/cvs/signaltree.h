#ifndef SIGNAL_TREE_H
#define SIGNAL_TREE_H

#include <cstring>
#include <string>
#include <QTextCodec>
#include <QString>
#include <QByteArray>

#include "treenode.h"
#include "mjutils.h"
#include "mj_cvs_spec.h"

TreeNode * create_cvs_in_tree(mj_cvs_t * mj);
TreeNode * create_cvs_out_tree(mj_cvs_t * mj);
TreeNode * create_cvs_params_tree(mj_cvs_t * mj);

#endif /* SIGNAL_TREE_H */