#ifndef SIGNAL_TREE_H
#define SIGNAL_TREE_H

#include <cstring>
#include <string>
#include <QTextCodec>
#include <QString>
#include <QByteArray>

#include "treenode.h"
#include "mjutils.h"
#include "mj_bup_pcm_spec.h"

TreeNode * create_bup_pcm_in_tree(mj_bup_pcm_t * mj);
TreeNode * create_bup_pcm_out_tree(mj_bup_pcm_t * mj);
TreeNode * create_bup_pcm_params_tree(mj_bup_pcm_t * mj);

#endif /* SIGNAL_TREE_H */