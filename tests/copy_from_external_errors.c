#include "fs/operations.h"
#include <assert.h>
#include <stdio.h>

int main() {
    char *path1 = "/f1";

    /* Tests different scenarios where tfs_copy_from_external_fs is expected to
     * fail */

    assert(tfs_init(NULL) != -1);

    int f1 = tfs_open(path1, TFS_O_CREAT);
    assert(f1 != -1);
    assert(tfs_close(f1) != -1);

    // Scenario 1: source file does not exist
    assert(tfs_copy_from_external_fs("./unexistent", path1) == -1);

    // Scenario 2:destination path is not valid
    assert(tfs_copy_from_external_fs("./unexistent", "unexistent") == -1);

    // Scenario 3: destination path is a directory
    assert(tfs_copy_from_external_fs("./unexistent", "/") == -1);

    // Scenario 4: destination file already exists its not for here tho
    //assert(tfs_copy_from_external_fs("./unexistent", path1) == -1);

    // Scenario 4: copying a file to a destination path that contains a file
    //that is currently open in the TFS
    assert(tfs_copy_from_external_fs("./unexistent", path1) == -1);

    // TODO: add more failure scenarios

    printf("Successful test.\n");

    return 0;
}
