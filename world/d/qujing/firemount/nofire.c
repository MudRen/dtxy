// room: nofire

inherit ROOM;

void create ()
{
  set ("short", "����ɽ");
  set("outdoors", "firemount");
  set ("long", @LONG

����Ѿ����������ˣ��Ĵ���ð��һ˿˿�Ĳ��̡�

������ʱ����Ĵ�����Ӱ˰�����ܴ�ݲ�������˵����̫����
��������¯���ŷ�������¯ש���ڴ˴�������Ϊ����ɽ����һ�߽�
ȥ�ȳ��̻ң������ᶫ��������

����һ�ж���ƽ���ˣ������������̾���ѡ�

LONG);

    set("exits", ([
               "northwest" : __DIR__"shanwai",
               "eastdown"  : __DIR__"shanbian",
             ]));
setup();
}

void init()
{
        object me;
    me=this_player();
     if (((me->query("fangcun/panlong_wzg_rsg")=="done")||(me->query("fangcun/panlong_wzg")=="done"))&&(me->query_temp("set_firemount")!="done"))
	{
		 me->add_temp("wzg_rulaifo",1);
		 me->set_temp("set_firemount","done");
	}
}
