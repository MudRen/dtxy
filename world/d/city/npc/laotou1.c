inherit NPC;

void create()
{
  string dir;
  set_name("��ݿ�����ͷ", ({"lao tou", "laotou", "lao", "tou"}) );
  set("gender", "����" );
  set("age", 22+random(10));
  set("per", 14);
  set("long","һ����ݵĿ�����ͷ��\n");

  set_temp("apply/attack", 30);
  set_temp("apply/defense", 30);
  set_skill("unarmed", 50);
  set_skill("dodge", 50);
  set_skill("parry", 50);
  set_skill("stick", 30);
  set("combat_exp", 15000);
  set("str", 25);
  set("attitude","heroism");
  setup();
  /*
  dir = __DIR__;
  dir[strlen(dir)-4] = 0;
  */
  dir = "/d/city/";
  add_money("silver", 2);
}

void init()
{
  object who;
  ::init();
  if (interactive(who = this_player()))
  {
     call_out("asking", 1, who);
  }
}

int accept_object (object who, object ob)
{
  object me;
  me = this_object();

  if ((! ob) ||
       ob->value() < 6000) 
  {
    message_vision ("$N������һ�ۣ����ŷ����˵㣬����ͷ�°뱲����ô�������\n", me);
    return 1;
  }  
  who->set_temp("has_paid", 2);
  me->remove_all_killer();
  message_vision ("$N��æ����������·��ָ��ָ���棬˵������������ร���ͷ֪���ɲ����ˡ���\n",me);
  return 1;
}

void asking(object who)
{
  object me;
  me = this_object();

  if (! who || environment(who) != environment())
    return;
  if (! living (me))
    return;

  if ((who && who->query_temp("has_paid") <= 0) 
	&& (string)who->query("family/family_name")!="��ׯ��1" )
  {
    message_vision ("$N���˹�������$n����һ������ͷ��֪ͨ���ݲ��ܽ�!\n",me,who);
    remove_call_out ("warning1");
      call_out("warning1", 5+random(5), who);
        call_out("killing", 25+random(5), who);
  }
  else
  { 
    message_vision ("$N��$n���˵�ͷ���ðɡ�\n",me,who);
    me->remove_all_killer();
  }
}

void warning1(object who)
{
  object me;
  me = this_object();

  if (who &&
      environment(who) == environment(me) &&
      living(me) &&
      who->query_temp("has_paid") <= 0)
  {
    message_vision ("$N���ͷ���˵������������Ϲ�䣬���ߡ����ߡ�\n",me,who);
  }
}


void killing(object who)
{
  object me;
  me = this_object();

  if (who &&
      environment(who) == environment(me) &&
      living(me) &&
      who->query_temp("has_paid") <= 0)
  {
    //me->kill_ob(who);
    //use command here...
    command("kill " + who->query("id"));
  }
}

