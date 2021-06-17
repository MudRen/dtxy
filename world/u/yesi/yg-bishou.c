
// ��������
//lestat 2001

inherit __DIR__"guai.c";
#include <ansi.h>

void set_skills(int max_value, int level)
{
        int guai_value;
        ::set_skills(max_value, level);
        
       	if (level==1) guai_value = max_value+max_value/8;
	else if (level==2) guai_value = max_value+max_value/6;
	else guai_value = max_value+max_value/4;
        set_skill("unarmed", guai_value+random(16));
        set_skill("dodge", guai_value+random(16));
        set_skill("parry", guai_value+random(16));
        set_skill("force", guai_value+random(16));
        set_skill("spells", guai_value+random(16));
 
        set_skill("sword",guai_value+random(16));
        set_skill("spysword",guai_value+random(16));
        set_skill("binfen-steps", guai_value+random(16));
        set_skill("mysticism", guai_value+random(16));
        set_skill("ice_fire_zhang", guai_value+random(16));
        set_skill("butian-force", guai_value+random(16));

        map_skill("force", "butian-force");
        map_skill("sword", "spysword");
        map_skill("parry", "spysword");
        map_skill("spells", "mysticism");
        map_skill("dodge", "binfen-steps");
        map_skill("unarmed", "ice_fire_zhang");
        create_family("����ɢ��",2 , "����");
	set("title",HIB"ͼ��ذ��"NOR);
        set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
        (: perform_action,"sword", "bishou" :),
        }) );
        carry_object("/d/obj/weapon/sword/qinghong.c")->wield();
        carry_object("/d/obj/cloth/shoupiqun.c")->wear();
}

