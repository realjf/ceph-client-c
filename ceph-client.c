#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rados/librados.h>

int main(int argc, const char **argv)
{
    rados_t cluster;
    char cluster_name[] = "ceph";
    char user_name[] = "client.admin";
    uint64_t flags;

    int err;
    // 创建集群句柄
    err = rados_create2(&cluster, cluster_name, user_name, flags);

    if(err < 0){
        fprintf(stderr, "%s:Couldn't create the cluster handle! %s \n", argv[0], strerror(-err));
        exit(EXIT_FAILURE);
    }else{
        printf("\nCreated a cluster handle.\n");
    }

    // 读取配置文件
    err = rados_conf_read_file(cluster, "/etc/ceph/ceph.conf");
    if(err < 0){
        fprintf(stderr, "%s: cannot read config file: %s\n", argv[0], strerror(-err));
        exit(EXIT_FAILURE);
    }else{
        printf("\nRead the config file.\n");
    }

    err = rados_conf_parse_argv(cluster, argc, argv);
    if(err < 0){
        fprintf(stderr, "%s: cannot parse command line arguments: %s\n", argv[0],  strerror(-err));
        exit(EXIT_FAILURE);
    }else{
        printf("\nRead the command line arguments.\n");
    }

    err = rados_connect(cluster);
    if(err < 0){
        fprintf(stderr, "%s: cannot connect to cluster: %s\n", argv[0], strerror(-err));
        exit(EXIT_FAILURE);
    }else{
        printf("\nConnected to the cluster.\n");
    }

    return 0;
}



