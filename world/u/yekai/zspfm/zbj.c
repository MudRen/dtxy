 //sgzl
#include <ansi.h>

inherit NPC;
string ask_for_zspfm();
void create()
{
  set_name(HIW"��˽�"NOR,({"zhu bajie","zhu","bajie"}));
  set("gender", "����");
  set("long",@LONG
������̰���վ�ȫ������Ԫ˧�ˡ�
����������ɮ����ȡ��������ǧ����࣬�����޳�������������������й�"ת����ѧ"����Ϣ��
LONG);
  set("title", HIY"��̳ʹ��"NOR);
  set("age", 35);
  set("attitude", "heroism");
  set("class", "xian");
  set("combat_exp", 2000000);
  set("daoxing", 2000000);
  set("kee", 2600);
  set("max_kee", 2600);
  set("sen", 2800);
  set("max_sen", 2800);
  set("force", 7000);
  set("max_force", 3500);
  set("mana", 7000);
  set("max_mana", 3500);
  set("force_factor", 40);
  set("mana_factor", 40);
  set("str", 40);
  set("per", 10);

  set_skill("unarmed", 200+random(50));
  set_skill("dodge", 200+random(50));
  set_skill("parry", 200+random(50));
  set_skill("rake", 200+random(50));
  set_skill("force", 200+random(50));
  set_skill("spells", 200+random(50));
  set_skill("baguazhou", 200+random(50));
  set_skill("yanxing-steps", 200+random(50));
  set_skill("skyriver-rake", 200+random(50));
  map_skill("force", "lengquan-force");
  map_skill("spells", "baguazhou");
  map_skill("rake", "skyriver-rake");
  map_skill("parry", "skyriver-rake");
  map_skill("dodge", "yanxing-steps");
  
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
}

string ask_for_zspfm() {
	object me=this_player();
	if (me->query("zspfm/number")>=2)
		return HIY"���Ѿ��������㹻��ľ�ѧ��!\n"NOR;
	if (me->query("zspfm/zspfm_zbj"))
		return HIY"�ҵľ�ѧ���Ѿ������ˣ�\n"NOR;
	if (me->query("lunhui_zhuanshi") < 3)
		return HIY"��ת���ϲ��������ҵľ�ѧ!\n"NOR;
	if (me->query("zspfm/zspfm_zbj_number")*20000000 > (me->query("combat_exp")+me->query("daoxing")))
		return HIY"�����Ϊ�����������򲻵���ѧ!\n"NOR;
	me->add("zspfm/zspfm_zbj_number",1);
	if (random(me->query("int")) > 45) {
		me->set("zspfm/zspfm_zbj",1);
		me->add("zspfm/number",1);
		message( "chat", HIY"\n��ת����ѧ������ϲ"+me->query("name")+"�ڵ�"+chinese_number(me->query("zspfm/zspfm_zbj_number"))+"�ε�ʱ�������˾�̳ʹ�ߵľ�ѧ��\n"NOR, users() );
		return HIY"��ϲ��ϲ����ɹ��������ҵľ�ѧ!\n"NOR;
	} else {
		return HIY"�ǳ��ź������Ե������û�������ҵľ�ѧ!\n"NOR;
	}
}


