// created by snowcat 12/2/1997

inherit ROOM;

void create ()
{
  set ("short", "��·");
  set ("long", @LONG

һ���̳������Ĵ�·����·ңң������ãã��ǰ�������˺�
�����ߡ�ʱ����Զ���޺�ʱ�����н������������߻�ɽҰ��
������֣��㲻�������ؼӿ첽����

LONG);

  set("exits", ([
        "east"    : __DIR__"dalu15",
        "west"    : "/d/qujing/yinwu/huangye7",
      ]));
  set("outdoors",__DIR__"");
  setup();
}

void init()
{
        object me;
    me=this_player();
     if (((me->query("fangcun/panlong_wzg_rsg")=="done")||(me->query("fangcun/panlong_wzg")=="done"))&&(me->query_temp("set_qinfa")!="done"))
	{
		 me->add_temp("wzg_rulaifo",1);
		 me->set_temp("set_qinfa","done");
	}
}

