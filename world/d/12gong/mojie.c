// by HAPP@YSZZ

inherit ROOM;
int block_cmd(string);
void create ()
{
        set ("short", "��ʮ��ɽ����");
        set ("long",             @LONG
�����˶�����������ʹ������˹�Ķ��ӣ�������ò�쳣���أ�����ɽ��ǡ��㼰����
�����Ǹ��ǳ���������ּҡ������˶����ݳ���������ִ��������֣����������ܱ�����
����������ˡ���һ�Σ���Ӧ���μӲ�Ϊ�����Ǵ���ʱ����������ͻȻ���ֲ��������ҡ�
�����ֱײ������ᣬ�����Ƕ��׷��߱ܡ��˶��ڻ�æ��Ҳ�������������޺��У���Ϊ̫
�����ŵĹ�ϵ��ֻ���°�������β�����ϰ����Ծɻ���ɽ���ģ������ͳ��˰�������
ɽ������
LONG);
        set("exits", ([
        "westup"    :       __DIR__"mj2bp1",
        "northdown"  :       __DIR__"rm2mj2",        
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/mojie" : 1,
        ]));
        set("outdoors", "12gong");
        setup();
}

int valid_leave(object me, string dir)
{
        if ( present("mo jie") && dir == "westup" )
        return notify_fail("����������ס���:�ȹ��������˵��\n");
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
