//sgzl
#include <ansi.h>

inherit NPC;

void create()
{
  set_name("��˽�",({"zhu bajie","bajie","zhu"}));
  set("gender", "����");
//  set("title", "����");
  set("age", 35);
  set("long", "    \nԭ���ǹ�����ӵĴ�Ԫ˧�����Ϸ�϶𱻱ᵽ�˼䡣\n");

  set("attitude", "heroism");
  set("class", "xian");
  set("combat_exp", 600000);
  set("daoxing", 600000);
  set("kee", 1500);
  set("max_kee", 1500);
  set("sen", 1500);
  set("max_sen", 1500);
  set("force", 1800);
  set("max_force", 1800);
  set("mana", 2000);
  set("max_mana", 2000);
  set("force_factor", 80);
  set("mana_factor", 80);
  set("str", 30);
  set("per", 13);


  set_skill("spells", 140);
  set_skill("dao", 140);
  set_skill("force", 140);
  set_skill("zhenyuan-force", 130);
  set_skill("rake", 140);
  set_skill("skyriver-rake", 160);
  set_skill("parry", 140);
  set_skill("yanxing-steps", 140);
  set_skill("dodge", 130);
  set_skill("unarmed", 150);
  set_skill("wuxing-quan", 150);


map_skill("spells", "dao");
map_skill("force", "zhenyuan-force");
map_skill("rake", "skyriver-rake");
map_skill("parry", "skyriver-rake");
map_skill("dodge", "yanxing-steps");
map_skill("unarmed", "wuxing-quan");
set("inquiry", ([
	"Ԫ˧" : "��ԭ�������ϵ�����Ԫ˧��"
]));


setup();

carry_object("/d/kaifeng/obj/jiuchipa")->wield();
carry_object("/d/obj/armor/tongjia")->wear();

}

int accept_fight(object me)
{
  message_vision("��˽������Ŀ���$Nһ�ۣ���Ȼ���������㣡\n", me);
  return 0;
}

void kill_ob (object ob)
{
  set_temp("no_return",1);
  set_temp("my_killer",ob);
  ::kill_ob(ob);
}

void die()
{
  object ob = query_temp("my_killer");
  object me = this_object();
  object temp_man; 
  if ((ob && ob->query("obstacle/gao")=="done") || 
  (ob && ob->query_temp("obstacle/gao_asked")!=1))
  {
     message_vision ("\n$N���һ������һ�ɿ�粻���ˡ�\n",me);   
     destruct(me);
   }

  if (ob && (ob->query_temp("obstacle/zhu_killed")==1) && (ob->query_temp("obstacle/zhu_shidong")==1))
  {
    message_vision ("\n$N���������������һ����˵�����������ܴӴ����ƣ�����ʦ����ɮ����ȡ������\n",me);
    call_out ("destruct_me",3,me);
    temp_man = new("/d/gao/npc/gao");
    temp_man->announce_success (ob);
  }
  else
  {
    ob->set_temp("obstacle/zhu_killed",1);
    message_vision ("\n$N���һ������һ�ɿ�粻���ˡ�\n",me);
    destruct(me);
  } 
  
}

