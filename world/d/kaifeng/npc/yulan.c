//ѩӰ 2000/2  ���Ծ�ɫ����ϵͳ
inherit NPC;

#include <quest_wr.h>
#include <reporting.h>

int test_player();

void create()
{
  set_name("����", ({"yu lan", "yu", "lan"}));
  set("gender", "Ů��");
  set("age", 25);
  set("per", 28);
  set("attitude", "peaceful");
  set("shen_type", 1);
  set("combat_exp", 4500);
  set_skill("unarmed", 40);
  set_skill("dodge", 40);
  set_skill("parry", 40);
  set_skill("force", 40);
  set_skill("spells", 40);
  set_skill("baihua-zhang", 40);
  set_skill("moondance", 40);
  set_skill("moonshentong", 40);
  map_skill("spells", "moonshentong");
  map_skill("unarmed", "baihua-zhang");
  map_skill("force", "moonforce");
  map_skill("spells", "moonshentong");
  set("max_gin",400);
  set("max_kee",400);
  set("max_sen",400);
  set("max_force",200);
  set("max_mana",200);
  set("force_factor",20);
  set("chat_chance",10);
  set("chat_msg",({
    "��������һЦ������Ь��½½����ļ���˲��١�\n",
    "�������һЦ˵������Щ����޵Ĺ��ＰȢ�׵Ĺ�����и���Ҳ��\n",
    "������˵�������˲����ˣ�����޵Ĺ�����������е��ױ�ˡ�\n",
    "����˵���������Ь����࣬������Щ���ε�����������һ���ˡ�\n",
  }));
  set("inquiry", ([
        "here":   "���˸�����ͤ��Ҳ�������ڴ�ļ������Ь�ڡ�\n",
        "name":   "�߼�С������Ҳ��\n",
        "wearing":   (: test_player() :),
        "����Ь��":   (: test_player() :),
        "ļ��":   (: test_player() :),
        "����":   (: test_player() :),
        "Ь��":   (: test_player() :),
        "��":   (: test_player() :),
        "Ь":   (: test_player() :),
        "��":   (: test_player() :),
      ]));
  setup();
  carry_object("/d/obj/cloth/pinkskirt")->wear();
  carry_object("/d/obj/cloth/shoes")->wear();
}

void rewarding (object who, object ob);

void init ()
{
  call_out ("check_player",1,this_player());
  add_action ("do_quxiao","quxiao");
  add_action ("do_quxiao","cancel");
}

int test_player()
{
  string *strs = ({
    "$N��$nһЦ���ⲻ����һ��������������Ҫ",
    "$N��$n������Ц����������������˵���˼��������ȡ��ϱ������ȱ",
    "$N��$n˵�����ɼ��ˣ��л��˼�Ҫ���ף�ûǮ�����ּ���",
    "$N��$n��ͷЦ��˵���������л�����˼�������ʲô",
    "$N΢Ц�Ŷ�$nһ��ͷ˵������������Ը��һ��ϲ�µ����仧��һ��",
  });  
  string str;
  object me = this_object();
  object who = this_player();
  int *quest_keys;
  string *quest;
  int delay;
  int i;

  if (who->query("quest/reward") > 0)
  {
    message_vision ("$N��$n˵������λ"+RANK_D->query_respect(who)+
                    "����������������ƻ��ƣ��β�ȥ���ٸ������������ͣ�\n",me,who);
    return 1;
  }

  if (who->query("quest/pending/wearing"))
  {
    message_vision ("$N��$n˵������λ"+RANK_D->query_respect(who)+
                    "�����ﻹ��������"+who->query("quest/pending/wearing/name")+"�أ�\n",me,who);
    return 1;
  }

  quest_keys = me->query_temp("quest_keys");
  if (! quest_keys)
  {
    quest_keys = sort_quests (quests_wearing);
    me->set_temp("quest_keys",quest_keys);
  }
  i = quest_accurate_index (quest_keys, who->query("combat_exp"));
  i = quest_random_index (quest_keys, i, who, "quest/cache/wearing");
  if (i == -1)
  {
    message_vision ("$N��$n̾��˵������λ"+RANK_D->query_respect(who)+
                    "�����������˲��٣����￴�������Ժ������ɡ�\n",me,who);
    return 1;
  }
  delay = MAXDELAY * i / sizeof(quest_keys) + DELAY_CONST + uptime();
  quest = quests_wearing[quest_keys[i]];
  who->set("quest/pending/wearing/index", i);
  who->set("quest/pending/wearing/daoxing", quest_keys[i]);
  who->set("quest/pending/wearing/name", quest[IDX_NAME]);
  who->set("quest/pending/wearing/id", quest[IDX_ID]);
  who->set("quest/pending/wearing/time", delay);
  str = strs[random(sizeof(strs))]+quest[IDX_NAME]+
        "��\n��λ"+RANK_D->query_respect(who)+
        "�ܷ����������취��\n";
  message_vision (str,me,who);
  informing (me,who,str);
  return 1;
}

void check_player (object who)
{
  object me = this_object();
  object ob;

  if (!who || !visible(who))
      return;

  if (! who || environment(who)!=environment(me))
    return;

  if (who->query("quest/reward") > 0)
  {
    message_vision ("$N��$n˵������λ"+RANK_D->query_respect(who)+
                    "�������ƻ��ƣ����ٸ������������ͣ�\n",me,who);
    return;
  }

  if (! who->query("quest/pending/wearing"))
    return;

  ob = present (who->query("quest/pending/wearing/id"),who);
  if (! ob || ! ob->query("no_give"))
    return;

  if (who->query("quest/pending/wearing/name") != ob->query("name"))
    return;

  message_vision ("$N��$n��������"+ob->query("name")+"��Ц����æ���˹�ȥ��\n",me,who);
  rewarding (who, ob);
  destruct (ob);
}

int accept_object(object who, object ob)
{
  object me = this_object();
  int t;

  if (who->query("quest/reward") > 0)
  {
    message_vision ("$N��$n˵������λ"+RANK_D->query_respect(who)+
                    "����������������ƻ��ƣ��β�ȥ���ٸ������������ͣ�\n",me,who);
    return 0;
  }

  if (! who->query("quest/pending/wearing"))
  {
    message_vision ("$N��$n˵����������ʱ����Ҫ�����\n",me,who);
    return 0;
  }

  if(ob->is_character()) return 0;
  
  if (who->query("quest/pending/wearing/name") != ob->query("name"))
  {
    message_vision ("$N��$n˵������λ"+RANK_D->query_respect(who)+
                    "������˵����Ҫ"+who->query("quest/pending/wearing/name")+
                    "������������"+ob->query("name")+"��������档\n",me,who);
    return 0;
  }

  if (who->query("quest/pending/wearing/id") != ob->query("id"))
  {
    message_vision ("$N��$n˵������λ"+RANK_D->query_respect(who)+
                    "����������Ҫ"+who->query("quest/pending/wearing/name")+
                    "��������ͦ�󣬵�����ͬһ����������Ҫ����("+
                    who->query("quest/pending/wearing/id")+")����������("+
                    ob->query("id")+")��\n",me,who);
    return 0;
  }

  t = who->query("quest/pending/wearing/time");

  if (t > uptime() && (t-MAXDELAY) <= uptime())
  {
    message_vision ("$N��$nҡͷ������ô��ͻ����ˣ�������Ҫ���Ҳ��\n",me,who);
    message_vision ("$N�ַԸ��������ٻ���"+chinese_number((t-uptime())/60+1)+
                    "����ȥѰѰ��\n",me,who);
    if (! DEBUG)
      return 0;
    else
      tell_object (who,"NOW DEBUG MODE: �ù���Ҫ�¶�����\n");
  }
  rewarding (who, ob);
  call_out ("destruct_ob",1,ob);
  return 1;
}

void destruct_ob (object ob)
{
  destruct (ob);
}

void rewarding (object who, object ob)
{
  object me = this_object();
  string reason;
  int reward;

  reason = "��"+me->query("name")+"Ѱ��"+ob->query("name")+"��";
  message_vision ("$N��$n˵������л��λ"+RANK_D->query_respect(who)+
                  reason+"����ø����ģ�\n",me,who);
  reward = quest_reward(who, quests_wearing, "wearing");
  who->add("quest/reward",reward);
  who->set("quest/reason",reason);
  who->add("quest/wearing/times",1);
  who->set_temp("quest/wearing/yun",1);
who->set_temp("quest/food/ok",0);
who->set_temp("quest/cloth/ok",0);
who->set_temp("quest/furniture/ok",0);
who->set_temp("quest/weapon/ok",0);
who->set_temp("quest/armor/ok",0);
who->set_temp("quest/ask/ok",0);
who->set_temp("quest/give/ok",0);
who->set_temp("quest/kill/ok",0);
  who->set_temp("quest/wearing/lasttime",time());
  who->set_temp("quest/wearing/ok",1);
  who->add("quest/wearing/reward",reward);
  reporting (who,reason, reward, "����");
  who->delete("quest/pending/wearing");
  call_out ("quest_done",1,who);
}


int do_quxiao (string arg)
{
  object who = this_player ();
  object silver = present ("gold",who);
  int amount, val;
  string item;
  object obj;
    obj=silver;
    amount=5;
if (!obj || (int)obj->query_amount() < 5)
           return notify_fail("������û����ô��Ļƽ�ѽ��\n");
obj->set_amount((int)obj->query_amount()-amount);
  who->delete("quest/pending/wearing");
write(HIC""+who->query("name")+"͵͵�ؽ��������������ƽ�\n�������˿�"+who->query("name")+"��Ц������ͦ�����¶��ģ��ðɣ���ξͷŹ��㡣\n"NOR);
return 1;
}
