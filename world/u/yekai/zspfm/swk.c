// demongorgon.c

#include <ansi.h>

inherit NPC;
string ask_for_zspfm();
void create()
{
	set_name( HIW "�����" NOR, ({ "sun xingzhe","swk","sun","xinzhe" }) );
	set("long",@LONG
���������������칬�����ʥ�ˡ�
����������ɮ����ȡ��������ǧ����࣬�����޳�������������������й�"ת����ѧ"����Ϣ��
LONG);

	set("age", 30);
          set("title", HIY"��սʤ��"NOR);
	set("max_gin", 3000);
	set("max_kee", 3000);
	set("max_sen", 3000);

	set("max_atman", 3000);
	set("atman", 3000);
      set("max_force", 5000);
      set("force", 10000);
      set("max_mana", 5000);
      set("mana", 10000);

	set("str", 40);
	set("cor", 40);
	set("cps", 40);
	set("spi", 40);
	set("int", 40);
	set("con", 40);
	set("kar", 40);
	set("per", 10);

	set("combat_exp", 3500000);
	set("daoxing", 2000000);

	set_skill("unarmed", 250+random(50));
        set_skill("dodge", 250+random(50));
        set_skill("parry", 250+random(50));
	set_skill("stick", 250+random(50));
	set_skill("spells", 250+random(50));
	set_skill("dao", 250+random(50));
	set_skill("puti-zhi", 250+random(50));
	set_skill("wuxiangforce", 250+random(50));
	set_skill("force", 250+random(50));
	set_skill("qianjun-bang", 250+random(50));
	set_skill("jindouyun", 250+random(50));
	
	map_skill("spells", "dao");
	map_skill("unarmed", "puti-zhi");
	map_skill("force", "wuxiangforce");
	map_skill("stick", "qianjun-bang");
	map_skill("parry", "qianjun-bang");
	map_skill("dodge", "jindouyun");
        set("force_factor",300);	
        set("mana_factor",300);
        set("bellicosity",300);
        set("nk_gain", 100+random(50));
        set("nk_factor", 12);
	/*
	set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
		(: cast_spell, "light" :),
		(: cast_spell, "dingshen" :),
                (: cast_spell, "thunder" :)
        }) );
	*/
	set_temp("apply/attack", 200);
	set_temp("apply/defense", 200);
	set_temp("apply/armor", 250);
	set_temp("apply/damage", 250);
	set("inquiry", ([
                "ת����ѧ" : (: ask_for_zspfm :),
                ]) );
	setup();
}
string ask_for_zspfm() {
	object me=this_player();
	if (me->query("zspfm/number")>=2)
		return HIY"���Ѿ��������㹻��ľ�ѧ��!\n"NOR;
	if (me->query("zspfm/zspfm_swk"))
		return HIY"�ҵľ�ѧ���Ѿ������ˣ�\n"NOR;
	if (me->query("lunhui_zhuanshi") < 4)
		return HIY"��ת���ϲ��������ҵľ�ѧ!\n"NOR;
	if (me->query("zspfm/zspfm_swk_number")*20000000 > (me->query("combat_exp")+me->query("daoxing")))
		return HIY"�����Ϊ�����������򲻵���ѧ!\n"NOR;
	me->add("zspfm/zspfm_swk_number",1);
	if (random(me->query("int")) > 45) {
		me->set("zspfm/zspfm_swk",1);
		me->add("zspfm/number",1);
		message( "chat", HIY"\n��ת����ѧ������ϲ"+me->query("name")+"�ڵ�"+chinese_number(me->query("zspfm/zspfm_swk_number"))+"�ε�ʱ�������˶�սʤ��ľ�ѧ��\n"NOR, users() );
		return HIY"��ϲ��ϲ����ɹ��������ҵľ�ѧ!\n"NOR;
	} else {
		return HIY"�ǳ��ź������Ե������û�������ҵľ�ѧ!\n"NOR;
	}
}

