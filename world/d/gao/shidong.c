// rewritten by xueshan on 09/11/2000
// Room: shidong

inherit ROOM;

void create ()
{
  set ("short", "ʯ��");
  set ("long", @LONG

�����������ʯ����ɽ�����ݶ��ɡ���������������ʵʵ��

LONG);

  set("light_up", 1);
  set("outdoors", "firemount");
  set("exits", ([
        "westdown" : __DIR__"shanlu2",
      ]));

  setup();
}

void init()
{
  add_action("do_za", "za");
}

int do_za (string arg)
{
  object me = this_player();
  object weapon = me->query_temp("weapon");

  if ((arg != "shimen" &&
       arg != "door"))
  {
    message_vision("$N����ʲô��\n",me);
    return 1;
  }
  
  if (! weapon)
  {
    message_vision ("$N�ಲ��������ȭͷ��ʯ����һ�ң�\n",me);
    message_vision ("�ҵ�һ��$Nֻ���ù�ͷ�������ˣ�\n",me);
    me->unconcious();
  }
  else
  {
    message_vision("$N���㾢������$n�������ȥ��\n",me,weapon);
    if (! this_object()->query("exits/south"))
    {
      message_vision ("�ҵ�һ���ſ��ˣ�\n",me);
      me->set_temp("obstacle/zhu_shidong",1);
    }
    else
    {
      	message_vision ("�ҵ�һ�������Ѿ��򿪵����ϣ�\n",me);
    }
    if (me->query("force") <= 1000)     
      me->unconcious();
    else
    {
      me->add("force",-200);
    }
    this_object()->set("exits/east", __DIR__"shandong");
    remove_call_out ("close");
    call_out ("close",60);
  }
    return 1;
}
