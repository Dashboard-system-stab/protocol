#ifndef SIGNAL_TREE_H
#define SIGNAL_TREE_H

#include <cstring>
#include <string>
#include <QTextCodec>
#include <QString>
#include <QByteArray>

#include "treenode.h"
#include "mjutils.h"
#include "mj_aufd_spec.h"

TreeNode * create_aufd_in_tree(mj_aufd_t * mj);
TreeNode * create_aufd_out_tree(mj_aufd_t * mj);
TreeNode * create_aufd_params_tree(mj_aufd_t * mj);

#endif /* SIGNAL_TREE_H */