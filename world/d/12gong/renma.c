// by HAPP@YSZZ

inherit ROOM;
int block_cmd(string);
void create ()
{
        set ("short", "�ھŹ�������");
        set ("long",
             @LONG
��ǰ�и����˰����壬�����ϰ���Ϊ�ˣ��°���Ϊ���Ұ�����塣Ȼ����һȺ�б�����
�˵��У�ֻ���ջ�֮�������˹�Ķ��ӿ�ũΪ�����İ��˰��������������֣�ռ��������
������˹����ʦ����һ�캣����˹���������ͻ����׷ɱ�����������ũ���У���ŭ�ĺ���
��˹����׼���������ƵƵ�ż���ȴ��֪��ʦ��ũҲ�������У����䵽���Ľš������մ��
����֮�������޷���ʹ���н�š���������������˹�˷����䲻��֮���������������
����Ϊ���ϵ���������

LONG);
        set("exits", ([
        "northup"    :       __DIR__"rm2mj1",
        "eastdown"  :       __DIR__"tx2rm2",        
        ]));

        set("objects", 
        ([ //sizeof() == 1
               __DIR__"obj/rm_cloth" : 1,
        ]));
        set("outdoors", "12gong");
        setup();
}

int valid_leave(object me, string dir)
{
        if ( present("sheshou shengyi") && dir == "northup" )
        return notify_fail("ǰ���·����һ�����ص�С�����ס��!\n");
        return ::valid_leave(me, dir);
}
void init()
{
    add_action("block_cmd", "", 1);
}
int block_cmd(string args)
{
string verb;
verb = query_verb();
    if (verb == "recall") return 1;
    return 0;
}
