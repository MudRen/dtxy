// by HAPP@YSZZ

inherit ROOM;
 int block_cmd(string);
void create ()
{
        set ("short", "��ʮһ��ˮƿ��");
        set ("long",             @LONG
����֮������˹������ϣ��������Ů����ɪ,�ǰ���ƥ˹������ϯ�У��д��͵���ְԱ��
�����޵����񸮺��̾�ְ��һֱ��ȱ�š�������˹���ڿ�����һ������Ӣ��������������
�������׵¡�������Ҳһ��ͬ�������������̾�һְ����˹����ʹ��ǰȥ���롣���Ǽ�����
�°������ɡ��ŵ��������Ҳ����Ӧ��˹�����롣��˹֪����ʮ�ַ�ŭ����������������
��ץ�أ�����ʹ����Զ���������ߵĹ���������ƿ�е�ˮ��Ϊ�������ܵ�ȪԴ�������ˮƿ
������Դ��
LONG);
        set("exits", ([
        "southup"    :       __DIR__"bp2sy1",
        "westdown"  :       __DIR__"mj2bp2",        
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/baoping" : 1,
        ]));
        set("outdoors", "12gong");
        setup();
}
int valid_leave(object me, string dir)
{
        if ( present("bao ping") && dir == "southup" )
        return notify_fail("���������˵��:�ȹ��������˵��\n");
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
