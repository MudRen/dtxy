// by HAPP@YSZZ

inherit ROOM;
int block_cmd(string);
void create ()
{
        set ("short", "���幬ʨ����");
        set ("long", @LONG
    ��˹�Ͱ���÷������֮�Ӻ�����˹��������ΪҮ��˹��˹����Ҫȥִ��ʮ�������ѵ�
���񣬵�һ���������Ʒ�����÷�ȵĲ���ʳ��ʨ����ֻʨ��ר�Լ���ʹ��ˣ�����η�壬
��ǰ���������Ʒ�����δ�������ߡ�������÷�ȵĺ�����˹Ҳ������·�ö��죬�ŷ���ʨ
�ӵ��ټ���������˹���������������ʨƤ̫Ӳ����Ч���ý�����Ҳ����ˣ����������
���Ƴɴֹ���������ʨͷ��ȥ����ʱ���¹�����ʨ��Ҳη�巢ŭ�ĺ�����˹����������˹
��ס���ӣ����ڱ������ˡ�Ů�����Ϊ�˸�����ֻʨ�ӣ���������������ʨ��������
LONG);


        set("exits", ([
        "northup"    :       __DIR__"sz2sn1",
        "eastdown"  :       __DIR__"jx2sz2",        
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/shizi" : 1,
        ]));
        set("outdoors", "12gong");
        setup();
}

int valid_leave(object me, string dir)
{
        if ( present("shi zi") && dir == "northup" )
        return notify_fail("��ŷ������Ц���ȹ��������˵��\n");
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
