// by HAPP@YSZZ

inherit ROOM;
int block_cmd(string);
void create ()
{
        set ("short", "��������Ů��");
        set ("long", @LONG
    ũҵŮ���ī�ض�����˹�������һŮ�������ݣ���һ������������Ұ��ժ��ʱ����
���Ϊ����������������ʢ���ţ�����������Ҫժʱ������ͻȻ�ѳɺü��飬�͵���ȥ��
��ĸ�׵�ī�ض�����ҲҪ�һ�ʧ�ٵ�Ů�����Ĵ�Ѱ�á������������龭����̫���������
˹�˸��ߵ�ī�ض�����ڤ������˹��Ȣ��������Ϊ�ޣ����������ص��£���ī�ض���Ϊ��
�˹��ȶ�ʹֲ���ή�����һë��������˹����̬���أ����򺣵�˹˵�飬���Ǻ���˹��
��������Ҫ��ʱ������ڤ��ʯ������ԣ�����������Ϊ�����뿪�����˳����ĸ��������
��һ�����ĸ���Ҫ����ڤ�磬���ĸ��¾ͱ�ý������ﲻ�˸��ֵĶ��죬��������һ�ص�
�˼���Ǵ��죬��ī�ض����Ǵ�Ů���Ļ���

LONG);


        set("exits", ([
        "westup"    :       __DIR__"sn2tc1",
        "northdown"  :       __DIR__"sz2sn2",        
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/shinu" : 1,
        ]));
        set("outdoors", "12gong");
        setup();
}

int valid_leave(object me, string dir)
{
        if ( present("shi nu") && dir == "westup" )
        return notify_fail("ɳ��ҡ��ҡͷ�������Ů��,�ȹ��������˵��\n");
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
