// by HAPP@YSZZ

inherit ROOM;
int block_cmd(string);
void create ()
{
        set ("short", "��ʮ����˫����");
        set ("long",             @LONG
��һ��������Ϊ������֮�ʣ����ں������硣�������ֵ������ǿ��ֵĳ���͵�������
�������൱���硣ͻȻ���������Ľ���������Ǽ���³���һ��β�ߣ�ӵ�д��������Ľ�
��������һ��������Ĵ����ߣ���˹��Ϊ�񣬰����޻�Ϊ��ѻ��������Ϊĵţ��������˹
��Ϊɽ��������Զ���֮�����롣������֮Ů�񰢸�����������������֮��Ү��˹�˻���
Ϊ�㣬�����ȷ�����˹���С���ʱ�˴˾����öд�������β�Ͱ���һ�������ֿ���������
˳���ӹ����������ѡ�ĸ������������β������������������������죬�����˫��������
����
LONG);
        set("exits", ([
        "north"    :       __DIR__"topalace1",
        "southdown"  :       __DIR__"bp2sy2",        
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/shuangyu" : 1,
        ]));
        set("outdoors", "12gong");
        setup();
}

int valid_leave(object me,string dir)
{
        
		if ( present("shuang yu") && dir == "north")
        
		return notify_fail("�����޵Ҵ�ŭ��:������˭,����ŵ����ȹ��������˵��\n");
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


