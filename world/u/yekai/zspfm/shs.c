 //sgzl
#include <ansi.h>

inherit NPC;
string ask_for_zspfm();
void create()
{
          set_name(HIW"ɳ����"NOR,({"sha heshang","sha","heshang"}));
          set("gender", "����");
          set("title", HIY"�����޺�"NOR);
		  set("long", @LONG
������ϰ���Դ��͵ľ������ˡ�
����������ɮ����ȡ��������ǧ����࣬�����޳�������������������й�"ת����ѧ"����Ϣ��
LONG);
          set("age", 23);
          set("per",10);        
          set("combat_exp", 1800000);
	  set("daoxing",1500000);
          set("per", 30);
          set("str", 30);
          set("max_kee", 2200);
          set("kee",2200);
          set("force_factor",20);
          set("max_sen", 1800);
          set("sen",1800);
          set("force", 6000);
          set("max_force", 3000);
          set("max_mana", 3000);
          set("mana", 6000);
          set_skill("unarmed", 180+random(50));
          set_skill("dodge", 180+random(50));
          set_skill("force", 180+random(50));
          set_skill("parry", 180+random(50));
          set_skill("staff", 180+random(50));
          set_skill("spells", 180+random(50));
          set_skill("buddhism",180+random(50));
          set_skill("jienan-zhi", 180+random(50));
          set_skill("lotusforce", 180+random(50));
          set_skill("lotusmove", 180+random(50));
          set_skill("lunhui-zhang", 180+random(50));
          map_skill("spells", "buddhism");
          map_skill("unarmed", "jienan-zhi");
          map_skill("force", "lotusforce");
          map_skill("staff", "lunhui-zhang");
          map_skill("parry", "lunhui-zhang");
          map_skill("dodge", "lotusmove");
          set_temp("apply/attack", 200); 
	  set_temp("apply/defense", 200);
	  set_temp("apply/armor", 200);
	  set_temp("apply/damage", 200);
          set("force_factor",300);
          set("mana_factor",300);
          set("bellicosity",300);
          set("nk_gain", 100+random(50));
          set("nk_factor", 12);
		set("inquiry", ([
                "ת����ѧ" : (: ask_for_zspfm :),
                ]) );
         setup();
         carry_object("/d/qujing/liusha/obj/staff")->wield();
}

string ask_for_zspfm() {
	object me=this_player();
	if (me->query("zspfm/number")>=2)
		return HIY"���Ѿ��������㹻��ľ�ѧ��!\n"NOR;
	if (me->query("zspfm/zspfm_shs"))
		return HIY"�ҵľ�ѧ���Ѿ������ˣ�\n"NOR;
	if (me->query("lunhui_zhuanshi") < 2)
		return HIY"��ת���ϲ��������ҵľ�ѧ!\n"NOR;
	if (me->query("zspfm/zspfm_shs_number")*20000000 > (me->query("combat_exp")+me->query("daoxing")))
		return HIY"�����Ϊ�����������򲻵���ѧ!\n"NOR;
	me->add("zspfm/zspfm_shs_number",1);
	if (random(me->query("int")) > 45) {
		me->set("zspfm/zspfm_shs",1);
		me->add("zspfm/number",1);
		message( "chat", HIY"\n��ת����ѧ������ϲ"+me->query("name")+"�ڵ�"+chinese_number(me->query("zspfm/zspfm_shs_number"))+"�ε�ʱ�������˽����޺��ľ�ѧ��\n"NOR, users() );
		return HIY"��ϲ��ϲ����ɹ��������ҵľ�ѧ!\n"NOR;
	} else {
		return HIY"�ǳ��ź������Ե������û�������ҵľ�ѧ!\n"NOR;
	}
}


