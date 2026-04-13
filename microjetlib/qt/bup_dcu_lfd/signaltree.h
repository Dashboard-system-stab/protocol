#ifndef SIGNAL_TREE_H
#define SIGNAL_TREE_H

#include <cstring>
#include <string>
#include <QTextCodec>
#include <QString>
#include <QByteArray>

#include "treenode.h"
#include "mjutils.h"
#include "mj_bup_dcu_lfd_spec.h"

TreeNode * create_bup_dcu_lfd_in_tree(mj_bup_dcu_lfd_t * mj);
TreeNode * create_bup_dcu_lfd_out_tree(mj_bup_dcu_lfd_t * mj);
TreeNode * create_bup_dcu_lfd_params_tree(mj_bup_dcu_lfd_t * mj);

#endif /* SIGNAL_TREE_H */