inherit __DIR__"guai.c";
#include <ansi.h>

void set_skills(int max_value, int level)
{
        int guai_value;
        ::set_skills(max_value, level);
        
       	if (level==1) guai_value = max_value+max_value/8;
	else if (level==2) guai_value = max_value+max_value/6;
	else guai_value = max_value+max_value/4;
        set("JQB_known",1);
        set_skill("puti-zhi", guai_value+random(16));
	set_skill("moondance", guai_value+random(16));
	set_skill("whip", guai_value+random(16));
	set_skill("jueqingbian", guai_value+random(16));
        set("title", HIY"Ц����"NOR);
	set_skill("wuxiangforce", guai_value+random(16));
	set_skill("literate", 180);
	set_skill("dao", guai_value+20+random(16));
	map_skill("spells", "dao");
	map_skill("force", "wuxiangforce");
	map_skill("unarmed", "puti-zhi");
	map_skill("whip", "jueqingbian");
	map_skill("parry", "jueqingbian");
	map_skill("dodge", "moondance");
	create_family("����ɽ���Ƕ�", 3, "����");
	set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
        (: perform_action,"unarmed", "xpt" :),
        }) );
	set("force_factor", query_skill("force")/2);
	set("mana_factor", query_skill("spells",1));
	                
        carry_object("/d/obj/cloth/shoupiqun.c")->wear();
}


