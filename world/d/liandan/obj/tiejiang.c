// By Canoe 2001-06-21
inherit F_VENDOR_SALE;
string give_map();
void create()
{
       set_name("�����ϳ�", ({"tie jiang","lao chen","tiejiang laochen",}));
       set("shop_id",({"laochen","tiejiang"}));
       set("shop_title","������");
       set("gender", "����");
       set("long",
"�ϳ���Ȼ������,����˳������ҩ�ġ�\n");
        set("combat_exp", 1000);
       set("age", 26);
       set("per", 14);
       set("attitude", "friendly");
       set("shen_type", 1);
       set_skill("unarmed", 10);
       set("chat_chance", 40);
       set("chat_msg", ({
"������������Ц����֪�뵽��ʲô��\n",
"�������ƺ��뵽��Щʲô,����¶�������Ц�ݣ�\n",

}) );

        set("vendor_goods", ([
                "yaochu": "/d/liandan/obj/yaochu",
                "gourou": "/d/ourhome/obj/gourou",
                "jitui": "/d/ourhome/obj/jitui",
                "taogan": "/d/obj/drug/fake-tao",
                "yao": "/d/obj/drug/jinchuang",
                "dan": "/d/obj/drug/hunyuandan",
        ]) );
        setup();

       carry_object("/d/obj/cloth/linen")->wear();
       add_money("silver", 1);
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_vendor_list", "list");
}

void greeting(object ob)
{
        if( !ob || !visible(ob) || environment(ob) != environment() ) return;
        switch( random(3) ) {  // 1/3 chance to greet.
                case 0:
        say( name()+"Ц�����˵������λ" +RANK_D->query_respect(ob) + "�������չ˵������?\n");
                        break;
        }
}
