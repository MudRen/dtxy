//Cracked by Roath

inherit ROOM;

void create ()
{
  set ("short", "ɽ·");
  set ("long", @LONG

�ߵ�ɽ·�ϣ�����Զ���Ĵ�ɽ������ô�ɽ���Ǹ��հ���ɽ�����
���ϣ�ɽ·����᫣�·�Ծ���Щ��ʯ��ľ��
LONG);

  set("exits", ([
        "westup"  : __DIR__"shanlu3",
        "east"  : __DIR__"shanpo",
      ]));
  set("outdoors","hfd");
  setup();
}

void init()
{
	object me=this_player();
	if (me->disable_player("<˯����>"))
	return;
	if (me->query_temp("need_sleep")=="yes")
	{
	message_vision("$N�ɻ�Ŀ������ܣ��������������龰��ȫ��ͬ��\n",me);
	tell_object(me,"�㷢�����Ϻ������Щ������\n");
	me->delete_temp("need_sleep");
	return;
	}
}






