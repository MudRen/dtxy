//sgzl
inherit ROOM;

void create ()
{
	set ("short", "ѩ��");
	set ("long", @LONG

ãã��ɽ����һ���޼ʵİ�ѩ���������ż���ǳǳ���㼣����Ȼ��
��Ԯ����һ���ѩɽ���ӣ��Ṧ��Ȼʮ���˵��ˡ�
��(jump)��ǰ���ʯ��(shi bi)�Ϳɵ���ѩɽ�Ķ����ˡ�
LONG);


	set("exits", 
	([ //sizeof() == 4
                "down" : __DIR__"xuejie-3",
                "west" : __DIR__"no4-w1",
                "east" : __DIR__"no4-e",
"up" : __DIR__"lingjiudong",
	]));
	set("objects", 
	([
                __DIR__"npc/chongzi" : 2,
	]));


	set("outdoors", "xueshan");

	setup();
}

void init()
{
        add_action("do_jump", "jump");
}


int do_jump(string arg)
{       
        object me;
        me=this_player();

        if ( !arg || ((arg != "shi bi") ))
                return notify_fail("��Ҫ��������\n");
        else if(me->query("kee")<50)   
          {
           message_vision("$N����һ������������������ˤȥ��\n",me);
           me->unconcious();
          }
        else if((int)me->query_skill("dodge", 1)<300)   
          {
           message_vision("$N��������һ�ݣ������ز������߾�һͷˤ��������\n",me);
           me->add("kee",-20); 
          }
	else
          {
           me->add("kee",-50); 
           message_vision("$N����һԾ�����ɵķ���ʯ�ڡ�\n",me);
           me->move("/d/xueshan/shanding");
           tell_room(environment(me),"ֻ��"+me->name()+"����Ծ��������\n", me);
           return 1;
           }
        return 1;
}
