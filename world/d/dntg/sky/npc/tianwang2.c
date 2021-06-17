//sgzl 

#include <ansi.h>
inherit NPC;
#include "huoyannpc2.h"
 
void create()
{
        set_name("ħ���", ({ "moli hong", "guangmu tianwang", "hong", "tianwang" }) );
        set("gender", "����" );
	set("long",
		"ħ���Ľ�֮һ��ʹһ�˷��컭ꪣ�����һ��ɡ����Ի������Ԫɡ����\n"
                "ɡ�����鴩�ɣ�����ĸ�̣���ĸ�̣�ҹ���飬�ٳ��飬�ٻ��飬��ˮ\n"
                "�飬�����飬�����飬�����飬�����顣�������鴩�ɡ�װ��Ǭ����\n"
                "���֣����ɡ���ҳţ��ſ�ʱ���ذ��������޹⣬תһתǬ���ζ���\n"
	);
	set("age",50);
	set("title", "��Ŀ����");
	set("attitude", "heroism");
	set("str",40);
	set("int",30);
	set("max_kee",1100);
	set("kee",1100);
	set("max_sen",1100);
	set("sen",1100);
	set("combat_exp",2000000);
    set("daoxing",1500000);
	set("force",2500);
	set("max_force",1500);
	set("mana",2500);
	set("max_mana",1600);
	set("force_factor", 80);
	set("mana_factor",80);
	
        set("eff_dx", 450000);
        set("nkgain", 500);

	set_skill("unarmed",150);
	set_skill("yingzhaogong", 200);
	set_skill("parry",200);
	set_skill("dodge",200);
	set_skill("spear",200);
	set_skill("bawang-qiang",200);
	set_skill("force",200);
	set_skill("spells", 200);
	set_skill("moshenbu", 200);
	map_skill("dodge", "moshenbu");
	map_skill("parry", "bawang-qiang");
	map_skill("spear","bawang-qiang");
	map_skill("unarmed", "yingzhaogong");
	set("inquiry", ([
		"name" : "���¹�Ŀ����ħ��죬��ʥ�Ͱ��ض����š�",
		"here" : "������Ƕ�����, ���ھ�������ˡ�",
	]) );

	setup();
	carry_object("/d/obj/weapon/spear/huaji")->wield();
	carry_object("/d/obj/armor/jinjia")->wear();
}

void hurting(object me, object ob)
{
   int n;
   
   remove_call_out("hurting");
   
   if(environment(me)!=environment(ob) || !me->is_fighting()) return;
   if(me->is_busy()) {
      call_out("hurting",6+random(5),me,ob);
      return;
   }
   
   message_vision(HIY"$n�ӻ��г����Ԫɡ���������˼��������Ԫɡ�����޵�������$N������\n"NOR,ob,me);
   n = 10 - (int)ob->query("daoxing")/(1 + (int)me->query("daoxing") ) -
      (int)ob->query("combat_exp")/(1+(int)me->query("combat_exp") );
   if(random(n)){
      me->start_busy( 60/ ((int)me->query_kar()+1));
      ob->start_busy(60/((int)ob->query_kar()+1) +1);
      message_vision("���$N����ס����ʱ�ж����ã�\n",ob);
   }
   else {
      me->start_busy( 30/ ( (int)me->query_kar()+1) );
      message_vision("$N����Ծ����Ԫɡ������������һ����\n",ob);
   }
   call_out("hurting",6+random(5),me,ob);
}

