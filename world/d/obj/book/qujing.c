
inherit ITEM;
void create()
{
  set_name("�����־���", ({"wuzi jing", "jing", "book"}));
  set_weight(1000);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("unit", "��");
    set("material", "paper");
    set("value", 0);
  //  set("no_put",1);
    set("no_give","��ô���Ķ��������������ˣ�\n");
    set("long", "һ�����������־���\n");
  }
}
void init ()
{
  object me = this_object();
  object who = this_player();
  object where = environment();
  add_action ("do_read", "read");
  add_action ("do_read", "study");
  add_action ("do_read", "du");
  add_action ("do_decide", "decide");
  if (! me->query("my_owner") &&
      interactive (who))
    me->set("my_owner",who->query("id"));
   
     if (userp(where))
  {
    if (me->query("owned"))
    {
      if (me->query("owned")!=where->query("id"))
      {
        call_out("destruct_me",1,where,me);
      }
    }
    else
    {
      me->set("owned",where->query("id"));
    }
  }
    
}

void destruct_me(object where, object me)
{
  message_vision("ǧ��ֹ�����������$n���ž���,��׷!\n",where,me);
  destruct (me);
}


void set_skill (string str)
{
  set("skill", ([
                "name": str,
                "exp_required": 10000,
                "sen_cost": 25,
                "difficulty": 25,
                "max_skill": 200,
  ]));
}
mapping skills = ([
  "archery": "��������",
  "axe": "��������",
  "blade": "��������",
  "dagger": "�̱���",
  "dodge": "�����Ṧ",
  "fork": "�����淨",
  "hammer": "��������",
  "mace": "����ﵷ�",
  "parry": "����ж��֮��",
  "rack": "�����ٷ�",
  "spear": "����ǹ��",
  "staff": "�����ȷ�",
  "stick": "��������",
  "sword": "��������",
  "throwing": "����ʹ��",
  "whip": "��������",
  "unarmed": "�˻���֮��",
  "force": "�ڹ��ķ�",
  "spells": "����",
  "literate": "����ʶ��",
]);
void show_skills ()
{
  int i;
  int size = sizeof (skills);
  string *strs = keys(skills);

  write ("�����ѡ�����¼��ܣ�\n");
  strs = (string *)sort_array (strs, 1);
  for (i = 0; i < size; i++)
  {
    write ("  "+strs[i]+": "+skills[strs[i]]+"\n");
  }
}
int do_decide (string arg)
{
  object me = this_object();
  object who = this_player();
  string *strs = keys(skills);
  string str;
  int i;
  int size = sizeof (skills);
  if (me->query("my_owner") != who->query("id")||! who->query("obstacle/reward"))
  {
    tell_object (who,"��ߴ�������������������Ȿ���鲻����ģ���֮���ã����ǻ��Ұɣ�\n");
    destruct (me);    return 1;
  }

  if (who->query("obstacle/book"))
  {
    str = skills[who->query("obstacle/book")];
    tell_object (who,"�����Ѿ��������־�ѧϰ"+str+"�ˡ�\n");
    return 1;
  }

  for (i = 0; i < size; i++)
  {
    if (arg == strs[i])
    {
      str = skills[arg];
      break;
    }
  }

  if (! str)
  {
    show_skills ();
    return 1;
  }
  who->set("obstacle/book",arg);
  me->set_skill(arg);
  tell_object (who,"������Ӵ������־�ѧϰ"+str+"��\n");
  tell_object (who,"����Խ�"+str+"ѧϰ�����ټ���\n");
  who->save();
  return 1;
}
int reading (object me, object book)
{
  mapping skill;
  int cost, my_skill,qint;

  if (environment(me)->query("no_fight") && 
      environment(me)->query("no_magic"))
    return notify_fail("��ȫ���ڽ�ֹ������\n");
                    
  if (me->is_fighting())
    return notify_fail("���޷���ս����ר�������ж���֪��\n");

  if (me->is_busy() || me->query_temp("pending/exercising"))
    return notify_fail("��������æ���ء�\n");

  if( !me->query_skill("literate", 1) )
    return notify_fail("���Ǹ���ä����ѧѧ����ʶ��(literate)�ɡ�\n");
  message_vision ("$N��ר�ĵ��ж�$n��\n",me,book);
  skill = book->query("skill");
  my_skill=me->query_skill(skill["name"],1);

  if ((int)me->query("combat_exp") < skill["exp_required"] ||
      ((string)SKILL_D(skill["name"])->type()=="martial"
      && my_skill*my_skill*my_skill/10>(int)me->query("combat_exp")))
  {
    write("��ĵ��в���������ô��Ҳû�á�\n");
    return 1;
  }

  notify_fail("����Ŀǰ����������û�а취ѧ������ܡ�\n");
  if (!SKILL_D(skill["name"])->valid_learn(me))
    return 0;
   qint=me->query_int();
   if(qint>40) qint=40;
  cost = skill["sen_cost"] + skill["sen_cost"] 
         * (skill["difficulty"] - qint)/20;
  if ((int)me->query("sen") < cost)
  {
    write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
    return 1;
  }
  if( me->query_skill(skill["name"], 1) > skill["max_skill"] )
  {
    write("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
    return 1;
  }
  me->receive_damage("sen", cost);

  if (!me->query_skill(skill["name"], 1))
    me->set_skill(skill["name"], 0);
  me->improve_skill(skill["name"], me->query_int()+5);
  write("���ж��й�" + to_chinese(skill["name"]) + "�ļ��ɣ��ƺ��е��ĵá�\n");
  return 1;
}
int do_read (string arg)
{
  object me = this_object();
  object who = this_player();

  if (! arg ||
      present (arg,who) != me)
    return notify_fail ("��Ҫ��ʲô��\n");

  if (me->query("my_owner") != who->query("id")||! who->query("obstacle/reward"))
  {
//    tell_object (who,"�Ȿ���鲻����ġ�\n");
    tell_object (who,"��ߴ�������������������Ȿ���鲻����ģ���֮���ã����ǻ��Ұɣ�\n");    destruct (me);    return 1;
  }

  if (! me->query("skill"))  
  {
    if (who->query("obstacle/book"))
      me->set_skill(who->query("obstacle/book"));
    else
    {
      tell_object (who,"��ʹ��decide�����������þ���ѧϰʲô��\n");
      return 1;
    }
  }
  return reading (who,me);
}
