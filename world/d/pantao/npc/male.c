// by snowcat 5/29/1997

#include <ansi.h>

inherit NPC;
int longwang();

void create()
{
  string *names = ({ "�ɹ�", "�ɽ�", "����", });
  string name = names[random(sizeof(names))];

  set_name(name,({ "xian" }) );
  set("gender", "����" );
  set("long", "һλ��緽���ܽ�عڵ�"+name+"��\n");
  set("age", 100+random(100));
  set("attitude", "peaceful");
  set("str", 50);
  set("per", 50);
  set("combat_exp",400000);
  set("force",500);
  set("max_force",500);
  set("force_factor", 100);
  set("max_gin", 4000);
  set("max_kee", 4000);
  set("max_sen", 4000);
  set("max_mana", 4000);
  set("mana", 400);
  set("mana_factor", 20);
  set_skill("unarmed",100);
  set_skill("dodge",100);
  set_skill("parry",100);
  set_skill("spear",100);
  set_skill("force",100);
  set("chat_chance",5);
  set("chat_msg",({(: random_move :)}));
          set("inquiry", ([
	    "��������" : (: longwang :),	    
	 ]) );
  setup();
  carry_object("/d/obj/cloth/xianpao")->wear();
}

int longwang()
{
	 object me,ob;
    me=this_player();
    ob=this_object();

	  if (!me->query_temp("longwang_yuan"))
	  return 0;
	  if (ob->query("name")!="�ɽ�")
	  return 0;
	command("nod" + me->query("id"));
	message_vision("\n�ɽ����ִ����"+RANK_D->query_respect(me)+"���ʱ��С��ֻ��֪�����࣬������������������ն֮�£�
	      ���»�����֪һ����\n",me);
	message_vision("\n����ǰ�գ�С�ɷ����ּ���������������ճ�ʱ���ƣ���ʱ���ף���ʱ���꣬δ
ʱ���㣬������ˮ������������ʮ�˵㣮˭֪������������Υּ���𣬵����գ�
��ʱ���ƣ���ʱ���ף�δʱ���꣬��ʱ��ֹ��ȴֻ����������ʮ�㣬����һ��ʱ
������������˵㣮��۴�ŭ��������ة��κ������ն�������������´�������
���������ֻ���İ�������գ���֪���ڿ��к�ת��\n",me);
	me->delete_temp("longwang_yuan");
	me->set_temp("longwang_xian",1);
	call_out("longwang1",2);
	return 1;
}

void longwang1()
{
	 object me,ob;
	 object jinzhi = new("/d/pantao/obj/jinzhi.c");
    me=this_player();
    ob=this_object();
	message_vision(WHT"\n$N����������ɷ��ģ��ҸմӶ������������Ƕ�����������������Ӧ��ûʲô
          ���ˣ�\n"NOR,me);
	message_vision("\n�ɽ���ͷ�����Ǿͺã�����ִ���½���ˮ���ɲ����к���ʧ���������°��պ���Ϊ
          ʳ��������ǰ�㶼�������ġ����ǵ���Ľ�ּ����ʱ����������ɱ���Ҿ�һֱ������ߣ�ϣ����������������\n",me);
        message_vision("\n�ɽ��ݸ���һ�Ž�ּ��\n",me);
        jinzhi->set("longgong_pass",1);
        jinzhi->move(me);
	message_vision(WHT"\n$N˵���������¾Ͳ�������ˣ���ǣ�\n"NOR,me);
}