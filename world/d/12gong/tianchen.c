// by HAPP@YSZZ

inherit ROOM;
int block_cmd(string);
void create ()
{
        set ("short", "���߹������");
        set ("long",
             @LONG
��������Ů����˹����˹��Ϊ�������ƶ����ʱ���õ���ӣ���˹������һֻ�ֳֳ�
��һֻ����ն��а��Ľ���Ϊ�����������۾������š���ǰ������������Ǻ�ƽ������
����ϣ�����ӵ����Զ���������������������ޡ���˼�į����ֻ�в��ϴ������࣬Ȼ��
��ʱ���˺ź���������ҵ���У������ڶ�����ʧ��֮��ص����ϡ�ֻ����˹����˹Ů����
���û�ȥ�����������ϣ�����Ϊ�ơ�������ˣ������Լ������䣬����ս�����𣬿�ʼ��
���ɱɱ���������˹����˹Ҳ����������ص����ϡ�����վ͸߹����Ӱ������ƽ����
���������


LONG);


        set("exits", ([
        "southup"    :       __DIR__"tc2tx1",
        "westdown"  :       __DIR__"sn2tc2",        
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/tiancheng" : 1,
        ]));
        set("outdoors", "12gong");
        setup();
}

int valid_leave(object me, string dir)
{
        if ( present("tian chen") && dir == "southup" )
        return notify_fail("ͯ��Ц��:�ȹ��������˵��\n");
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
