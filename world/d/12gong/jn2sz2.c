// by HAPP@YSZZ

inherit ROOM;
int block_cmd(string);
void leave_here(object me) {
   if(me) me->move("/d/12gong/szchoose");
}

void create ()
{
        set ("short", "ɽ·");
        set ("long", @LONG

��������˫�ӹ���·�ϣ�ֻ��ǰ����Կ���������˫�ӹ������ڰ���
ƥ�Ƿ��ϣ�����������ԼԼ�����Կ���ɽ�µĽ�ţ����
LONG);


        set("exits", ([
        "eastup"    :       __DIR__"shuangzi",
            "southdown"  :       __DIR__"jn2sz1",
        ]));

        set("outdoors", "12gong");
        setup();
}


int valid_leave(object me, string dir)
{
        if (dir == "eastup" && me->query_temp("12gong/cike") != "done")
	       {
			 
         call_out("leave_here",1,me);
      return notify_fail("��һ����ã��\n");
		   }
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
