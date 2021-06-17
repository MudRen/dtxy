// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
//self-made fabao room

#include <ansi.h>
#include <weapon.h>
#include <armor.h>
#include <login.h>

inherit ROOM;

#define MAX_FABAO   3

int  do_sm();
int  do_dispose(string arg);
int  do_upgrade(string arg);
int  do_list();
int  do_cost(string arg);

void get_type(string arg, object ob);
void get_subtype(string arg, object ob);
void get_id(string arg, object ob);
void get_name(string arg, object ob);
void get_desc(string arg, object ob);
void get_unit(string arg, object ob);
void build_weapon(object ob);
void build_armor(object ob);
int check_legal_name(string name, int max_len);
int check_legal_id(string name);
void confirm_dispose(string arg, object ob, object fabao_ob);

void init()
{
    add_action("do_sm", "make_fabao");
    add_action("do_dispose", "dispose");
    add_action("do_list", "list");
    add_action("do_cost", "cost");
    add_action("do_upgrade", "upgrade");
    add_action("do_change_name", "change_name");
    add_action("do_change_id", "change_id");
    add_action("do_change_desc", "change_desc");
    add_action("do_change_unit", "change_unit");

   seteuid(getuid());
}

void create ()
{
        set ("short", "Ů洲��촦");
        set ("long", @LONG

������һƬ�����ء�����������һ����һ�����ι�״ɫ�ʰ�쵵�
������ʯ����ѩɫӳ����������⡣����һ���ʯ�Ͽ��ż��д�
�֣�

     ���ؾ���
     Ů洲���
     ��ʯδ��
     �Ÿ�����

���»���������ؿ���һƪС��(words)����Զ��Ҳ������˵����
ʲô��
LONG);

        set("item_desc", ([ "words" : 
             "make_fabao     ���Ʒ���\n" +
             "dispose        ע������\n" +
             "list           �оٿ��Ʒ�������\n" +
             "upgrade        ��������\n" +
             "cost ����      �������Ƽ��������ܷ���\n" +
             "change_name    ����������\n" +
             "change_id      �������Ĵ���\n" +
             "change_desc    ������������\n" +
             "change_unit    �������ĵ�λ����\n\n" +
             HIY+"�������а취��\n"+NOR+
             "����ÿ���������һ���ǣ����Ϊ���ǡ�\n"+
             "���������Լ�һ��Ϊ�����׼������������Ҫ\n" + 
             "����100 ����У�������Ҫ 500�꣬��ô����\n" +
             "�����Ǻ�ÿ����������Ҫ 80 ����С�\n", ]));

        set("exits", 
        ([ //sizeof() == 1 
                "east" : __DIR__"fabao-road2",
        ]));


   set("no_fight", 1);
   set("no_magic", 1);

    setup();
}

int do_sm()
{
    object me = this_player();
   int  fabao_num;
   
   if( me->query("balance") < 500000 )
      return notify_fail("����������̫�ߣ�������ȥ���ưɡ�\n");
      
   if( me->query("combat_exp") < 20000)
     return notify_fail("��ĵ��в������������취����\n");
   
   if( me->query("max_force") < 300 )
     return notify_fail("��������������������취����\n");
     
   if( me->query("max_mana") < 300)
     return notify_fail("��ķ����������������취����\n");
   
   if( me->query("force") < (me->query("max_force")+100) )
     return notify_fail("����������㣬�������취����\n");
   
   if( me->query("mana") < (me->query("max_mana")+100) )
     return notify_fail("���Ŀǰ�������㣬�������취����\n");
   
//   if( me->query("kee") != me->query("max_kee") ||
//       me->query("sen") != me->query("max_sen") ) 
//     return notify_fail("��ľ������㣬�������취����\n");

    fabao_num = 0;     
   if( me->query("fabao/weapon") )     fabao_num++;
   if( me->query("fabao/armor1") )     fabao_num++;
   if( me->query("fabao/armor2") )     fabao_num++;
   
   if( fabao_num >= MAX_FABAO )
     return notify_fail("�㲻�������Ʒ����ˣ����� dispose ע����Ҫ�ķ�����\n");
     
   write("��Ҫ�����෨����\n");
   if( !me->query("fabao/weapon") )
     write("w. ����\n");
   if( !me->query("fabao/armor1") || !me->query("fabao/armor2") )
     write("a. ����\n");
   write("o. ����(��ȱ)\n");

   seteuid(getuid());
   // Other kinds of fabao can be added too.. if there is somefile
   // we can use as a default object.
   write("��ѡ��(q ��ȡ��)");
   input_to( (: get_type :), me );
   
   return 1;   
}

void get_type(string arg, object ob)
{
   if( arg == "q" || arg == "Q" )
      return;

   if( (arg != "w" || ob->query("fabao/weapon"))
     && (arg != "a" || ( ob->query("fabao/armor1")
     && ob->query("fabao/armor2") )) )   {
     write("��Ҫ�����෨����\n");
     if( !ob->query("fabao/weapon") )
        write("w. ����\n");
     if( !ob->query("fabao/armor1") || !ob->query("fabao/armor2") )
        write("a. ����\n");
       write("o. ����(��ȱ)\n");
       write("��ѡ��(q ��ȡ��)");
     input_to( (: get_type :), ob );
     return;
   }

   if( arg == "w" )    {
     ob->set_temp("fabao_type", "weapon");
     write("\n");
     write("��ѡ���������ࣺ\n");
     write("1. ��  2. ��  3. ��  4. ��  5. �  6. ǹ\n");
     write("7. ��  8. ��  9. ��  10. ��\n");
       write("��ѡ��(q ��ȡ��)");
   }
   else if( arg == "a" )   {
     ob->set_temp("fabao_type", "armor");
     write("\n");
     write("��ѡ��������ࣺ\n");
     write("1. ��  2. Ь  3. �·�  4. ָ��  5. ����  6. ͷ��\n");
     write("7. ����  8. ��  9. ����  10. ����  11. ����\n");
       write("��ѡ��(q ��ȡ��)");
   }
   input_to( (: get_subtype :), ob);
}

void get_subtype(string arg, object ob)
{
    int  order;
   string fabao_type = ob->query_temp("fabao_type");
   
   if( arg == "q" || arg == "Q" )    return;

    sscanf(arg, "%d", order);
    
   if( (fabao_type == "weapon" && order <= 0 && order > 10) ||
     (fabao_type == "armor" && order <= 0 && order > 11) )  {
     if( arg == "w" )    {
        fabao_type = "weapon";
        write("\n");
        write("��ѡ���������ࣺ\n");
        write("1. ��  2. ��  3. ��  4. ��  5. �  6. ǹ\n");
        write("7. ��  8. ��  9. ��  10. ��\n");
           write("��ѡ��(q ��ȡ��)");
     }
     else if( arg == "a" )   {
        fabao_type = "armor";   
        write("\n");
        write("��ѡ��������ࣺ\n");
        write("1. ��  2. Ь  3. �·�  4. ָ��  5. ����  6. ͷ��\n");
        write("7. ����  8. ��  9. ����  10. ����  11. ����\n");
           write("��ѡ��(q ��ȡ��)");
     }
     ob->set_temp("fabao_type", fabao_type);
     input_to( (: get_subtype :), ob);
     return;
   }
   
   ob->set_temp("fabao_subtype",  order);

   write("\n");
   write("���趨Ӣ�� id ��");
   input_to( (: get_id :), ob ); 
}


int check_legal_id(string id)
{
   int i;
   string   *legalid;
   
   i = strlen(id);
    if( (strlen(id) < 3) || (strlen(id) > 20 ) ) {
     write("�Բ���Ӣ�� id ������ 3 �� 20 ��Ӣ����ĸ��\n");
     return 0;
    }
    while(i--)
       if( id[i] != ' ' && (id[i]<'a' || id[i]>'z') )  {
         write("�Բ���Ӣ�� id ֻ����Ӣ����ĸ��\n");
         return 0;
       }
    
    legalid = explode(read_file(BANNED_ID), "\n");
    for(i=0; i<sizeof(legalid); i++)   {
       if( id == legalid[i] )   {
         write("�Բ������� id ����������˵����š�\n");
         return 0;
       }
    }
    
    return 1;
}


int check_legal_name(string name, int max_len)
{
   int i;
   string   *legalname;     //not implemented..may add later
   
   i = strlen(name);
    if( (strlen(name) < 2) || (strlen(name) > max_len ) ) {
       write( sprintf("�Բ��𣬷��������ֱ����� 1 �� %d �������֡�\n",
        max_len/2) );
     return 0;
    }
    while(i--)   {
       if( name[i]<=' ' )   {
         write("�Բ��𣬷��������ֲ����ÿ�����Ԫ��\n");
         return 0;
       }
       if( i%2==0 && !is_chinese(name[i..<0]) )  {
         write("�Բ��������á����ġ�������ȡ���֡�\n");
         return 0;
       }
    }
   
    return 1; 
}


void get_id(string arg, object ob)
{
   arg = lower_case(arg);
   if( !check_legal_id(arg) )   {
     write("���趨Ӣ�� id ��");
     input_to( (: get_id :), ob ); 
     return;
   }

   arg = replace_string(arg, " ", "_");   
   ob->set_temp("fabao_id",arg);
   
   write("\n");
   write("���趨��������(�ɼ���ɫ)");
   input_to( (: get_name :), ob);
}

void get_name(string arg, object ob)
{
   string  arg_old;
   
   arg += "$NOR$";
   arg_old = arg;
        arg = replace_string(arg, "$BLK$", "");
        arg = replace_string(arg, "$RED$", "");
        arg = replace_string(arg, "$GRN$", "");
        arg = replace_string(arg, "$YEL$", "");
        arg = replace_string(arg, "$BLU$", "");
        arg = replace_string(arg, "$MAG$", "");
        arg = replace_string(arg, "$CYN$", "");
        arg = replace_string(arg, "$WHT$", "");
        arg = replace_string(arg, "$HIR$", "");
        arg = replace_string(arg, "$HIG$", "");
        arg = replace_string(arg, "$HIY$", "");
        arg = replace_string(arg, "$HIB$", "");
        arg = replace_string(arg, "$HIM$", "");
        arg = replace_string(arg, "$HIC$", "");
        arg = replace_string(arg, "$HIW$", "");
        arg = replace_string(arg, "$NOR$", "");

   if( !check_legal_name(arg, 12) )  {
        write("���趨��������(�ɼ���ɫ)");
     input_to( (: get_name :), ob);
     return;
   }

   arg = arg_old;

        arg = replace_string(arg, "$BLK$", BLK);
        arg = replace_string(arg, "$RED$", RED);
        arg = replace_string(arg, "$GRN$", GRN);
        arg = replace_string(arg, "$YEL$", YEL);
        arg = replace_string(arg, "$BLU$", BLU);
        arg = replace_string(arg, "$MAG$", MAG);
        arg = replace_string(arg, "$CYN$", CYN);
        arg = replace_string(arg, "$WHT$", WHT);
        arg = replace_string(arg, "$HIR$", HIR);
        arg = replace_string(arg, "$HIG$", HIG);
        arg = replace_string(arg, "$HIY$", HIY);
        arg = replace_string(arg, "$HIB$", HIB);
        arg = replace_string(arg, "$HIM$", HIM);
        arg = replace_string(arg, "$HIC$", HIC);
        arg = replace_string(arg, "$HIW$", HIW);
        arg = replace_string(arg, "$NOR$", NOR);
   
   ob->set_temp("fabao_name", arg + NOR);
   
   write("\n");
   write("������������");
   input_to( (: get_desc :), ob);
}

void get_desc(string arg, object ob)
{
   if( !check_legal_name(arg, 60) )  {
     write("������������");
     input_to( (: get_desc :), ob);
     return;
   }

   ob->set_temp("fabao_desc",  arg);
   
   write("\n");
   write("���������ʣ�(Return for default)");
   input_to( (: get_unit :), ob);
}


void get_unit(string arg, object ob)
{
   string fabao_unit, fabao_type;

    if( arg == "" )
       fabao_unit = "";
   else if( !check_legal_name(arg, 2) )  {
       write("���������ʣ�(Return for defult)");
      input_to( (: get_unit :), ob);
      return;
    }
    else
       fabao_unit = arg; 
   
   fabao_type = ob->query_temp("fabao_type");
   ob->set_temp("fabao_unit", fabao_unit);
   if( fabao_type == "weapon" )
     build_weapon(ob);   
   else if( fabao_type == "armor" )
     build_armor(ob);   
   // may have more later
}

void build_weapon(object ob)
{
   object newob;
   string weapon_dir, ob_file;
   string *id_list, *t_list;
   int rev;
   int    fabao_subtype = ob->query_temp("fabao_subtype");
   string fabao_id = ob->query_temp("fabao_id");
   string fabao_name = ob->query_temp("fabao_name");
   string fabao_desc = ob->query_temp("fabao_desc");
   string fabao_unit = ob->query_temp("fabao_unit");
   
   newob = new("/obj/fabao");
   if(!newob)
     return;
     
   seteuid(fabao_id);
   rev = export_uid(newob);
   seteuid(getuid());

   newob->set("value", 1);
   newob->set("no_get", 1);   
   newob->set("no_give", 1);   
   newob->set("no_sell", 1);   
   newob->set("no_drop", 1);   
   newob->set("no_put", 1);   
   
   weapon_dir = "/d/obj/weapon/";
   newob->set("weapon_prop/damage", 10);
   newob->set("flag", TWO_HANDED);
   newob->set("weight", 1000);
   switch( fabao_subtype )   {
     case 1:
        ob_file = weapon_dir + "axe/bigaxe";
        break;
     case 2:
        ob_file = weapon_dir + "blade/blade";
        break;
     case 3:
        ob_file = weapon_dir + "fork/gangcha";
        break;
     case 4:
        ob_file = weapon_dir + "hammer/hammer";
        break;
     case 5:
        ob_file = weapon_dir + "mace/ironmace";
        break;
     case 6:
        ob_file = weapon_dir + "spear/gangqiang";
        break;
     case 7:
        ob_file = weapon_dir + "staff/muzhang";
        break;
     case 8:
        ob_file = weapon_dir + "stick/qimeigun";
        break;
     case 9:
        ob_file = weapon_dir + "sword/changjian";
        break;
     case 10:
        ob_file = weapon_dir + "whip/pibian";
        break;
   }

   newob->set_default_object( ob_file );
   
   newob->set("long", fabao_desc);
   newob->set("stars/damage", 1);
   newob->set("upgraded/damage", 0);
   if( fabao_unit != "" )
      newob->set("unit", fabao_unit);
   id_list = ({ fabao_id });
   t_list = explode( fabao_id, "_");
   if( sizeof(t_list) > 1 )   {
     id_list += t_list;
   }
   newob->set_name( fabao_name, id_list ); 

   // set owner of fabao
   newob->set("owner_id", getuid(ob));
   newob->set("series_no", "1");
   newob->set("default_file", ob_file);


    newob->save();   

   //ob->add("max_force", -50);
   //ob->add("max_mana", -50);
   ob->add("force", -200);
   ob->add("mana", -200);
   ob->add("balance", -500000);

   ob->set("fabao/weapon",  newob->query("series_no"));

   newob->setup();
   if( !newob->move(ob) )
      newob->move(environment(ob));
   ob->save();
   
   write("�������Ƴɹ���\n");

   return;
}

void build_armor(object ob)
{
   object   newob;
   string   armor_dir, ob_file;
   string   *id_list, *t_list;
   int     rev;
   string  fabao_id = ob->query_temp("fabao_id");
   string  fabao_name = ob->query_temp("fabao_name");
   string  fabao_desc = ob->query_temp("fabao_desc");
   string  fabao_unit = ob->query_temp("fabao_unit");
   int     fabao_subtype = ob->query_temp("fabao_subtype");

   newob = new("/obj/fabao");
   if(!newob)
     return;
   
   seteuid(fabao_id);
   rev = export_uid(newob);
   seteuid(getuid());

   newob->set("value", 1);
   newob->set("no_get", 1);   
   newob->set("no_sell", 1);   
   newob->set("no_give", 1);   
   newob->set("no_drop", 1);   
   newob->set("no_put", 1);   

   armor_dir = "/d/obj/";
   newob->set("armor_prop/armor", 5);     
   newob->set("armor_prop/dodge", 0);     
   newob->set("armor_prop/spells", 0);
   newob->set("weight", 1000);
   // anything else need to be set?
   
   switch( fabao_subtype )   {
   
   // Add ob_file if you can find the same kind of file
     case 1:
        ob_file = armor_dir + "armor/tenjia";
        break;
     case 2:
        ob_file = armor_dir + "cloth/buxie";
        break;
     case 3:
        ob_file = armor_dir + "cloth/linen";
        break;
     case 4:
        ob_file = armor_dir + "cloth/ring";
        break;
     case 5:
        ob_file = armor_dir + "cloth/gloves";
        break;
     case 6:
        ob_file = armor_dir + "cloth/hat";
        break;
     case 7:
        ob_file = armor_dir + "cloth/necklace";
        break;
     case 8:
        ob_file = armor_dir + "armor/niupi";
        break;
     case 9:
        ob_file = armor_dir + "cloth/surcoat";
        break;
     case 10:
        ob_file = armor_dir + "cloth/wrists";
        break;
     case 11:
        ob_file = armor_dir + "cloth/belt";
        break;
   }
   
   newob->set_default_object( ob_file );
   
   newob->set("long", fabao_desc);
   newob->set("stars/dodge", 1);
   newob->set("stars/armor", 1);
   newob->set("stars/armor_vs_force", 1);
   newob->set("stars/spells", 1);
   newob->set("stars/armor_vs_spells", 1);
   newob->set("upgraded/dodge", 0);
   newob->set("upgraded/armor", 0);
   newob->set("upgraded/armor_vs_force", 0);
   newob->set("upgraded/spells", 0);
   newob->set("upgraded/armor_vs_spells", 0);
   if( fabao_unit != "" )
      newob->set("unit", fabao_unit);
   id_list = ({ fabao_id });
   t_list = explode( fabao_id, "_");
   if( sizeof(t_list) > 1 )   {
     id_list += t_list;
   }
   newob->set_name( fabao_name, id_list ); 

   // set owner of fabao
   newob->set("owner_id", getuid(ob));
   if( !ob->query("fabao/armor1") )
     newob->set("series_no", "2");
   else if( !ob->query("fabao/armor2") )
     newob->set("series_no", "3");
   newob->set("default_file", ob_file);

    newob->save();   

   //ob->add("max_force", -50);
   //ob->add("max_mana", -50);
   ob->add("force", -200);
   ob->add("mana", -200);
   ob->add("balance", -500000);
   
   if( !ob->query("fabao/armor1") )
     ob->set("fabao/armor1",  newob->query("series_no"));
   else if( !ob->query("fabao/armor2") )
     ob->set("fabao/armor2",  newob->query("series_no"));
   
   newob->setup();
   if( !newob->move(ob) )
      newob->move(environment(ob));
   ob->save();

   write("�������Ƴɹ���\n");
   
   return;
}

int  do_dispose(string arg)
{
   object ob = this_player();
   object fabao_ob;
  
   if( !arg || arg == "" )
     return notify_fail("��Ҫ����ʲô������\n");

   if( !objectp(fabao_ob=present(arg, ob)) )
      return notify_fail("������û��������������\n");
      
   if(!fabao_ob->query("owner_id") || !fabao_ob->query("series_no")) 
      return notify_fail("�Ǹ����Ƿ���Ү��\n");
      
   write("��ȷ��Ҫ����÷�����(y/n)");
   input_to( (: confirm_dispose :), ob, fabao_ob); 
   return 1;
}

void confirm_dispose(string arg, object ob, object fabao_ob)
{
   mapping  fabao_list;
   string*  names;
   int      i;

   if( arg == "y" || arg == "Y" )  {
     fabao_list = ob->query("fabao");
     if( !mapp(fabao_list) )     return;
     names = keys(fabao_list);
     for(i=0; i<sizeof(names); i++)  {
      if( fabao_list[names[i]] == fabao_ob->query("series_no") )  {
        //seteuid(getuid(ob));
        //rm( fabao_ob->query_save_file() + __SAVE_EXTENSION__ );
        ob->delete("fabao/"+names[i]);
        destruct( fabao_ob );
        write("�����������ˡ�\n");
        break;
      }
     }
   }

   return;
}

int  do_list()
{
    write("Ŀǰ���취�������У�\n");   
    write("w. �����ࣺ\n");
   write("       ��  ��  ��  ��  �  ǹ\n");
   write("       ��  ��  ��  ��\n\n");
   write("a. �����ࣺ\n");
   write("       ����  Ь  �·�  ָ��  ����  ͷ��\n");
   write("       ����  ��  ����  ����   ����\n\n");
   write("Ŀǰ�������������ࣺ\n");
    write("w. ������\n");
   write("       ���˺���\n\n");
   write("a. �����ࣺ\n");
   write("       �ӷ�����\n");
   write("       �ӵֿ���\n");
   write("       ���ڹ��ֿ���\n");
   write("       ��ħ��������\n");
   write("       ��ħ���ֿ���\n");

   return 1;   
}

int do_cost(string arg)
{
   object fabao_ob, me=this_player();
   int i, damage_stars, dodge_stars, armor_stars, force_stars;
   int spells_stars, vs_spells_stars;
   
   if( !arg || arg == "" )  {
      write("���취����Ҫ��ʮ���ƽ����ٵ�������ħ����\n");
      write("���ҵ��б����ڶ�ʮ�����ϣ����������������\n");
      write("���� 300���ϡ�������������� 1500/1200����\n");
      write("�߳�����300����������ħ�����ơ�\n");
      return 1;
   }
  
   if( !objectp(fabao_ob=present(arg, me)) )
      return notify_fail("������û��������������\n");
      
   if(!fabao_ob->query("owner_id") || !fabao_ob->query("series_no")) 
      return notify_fail("�Ǹ����Ƿ���Ү��\n");
      
   if( fabao_ob->query("series_no") == "1" )  {
      write("�����ȼ���    " + HIR);
      damage_stars = fabao_ob->query("stars/damage");
      for(i=0; i<damage_stars; i++)
         write("��");
      write(NOR + "\n");
      write(HIG+"�˺���" + NOR+ "(damage)������Ҫ��\n");
      switch(damage_stars)  {
         case 1:  write("    ����һ��������\n");
                  write("    �����������\n");
                  write("    �������������ʮ��\n");
                  write("    ���ĵ���һ��\n");
                  break;
         case 2:  write("    �������������\n");
                  write("    ����һǧ����\n");
                  write("    �����������һ�ٵ�\n");
                  write("    ���ĵ���ʮ��\n");
                  break;
         case 3:  write("    ����һǧ������\n");
                  write("    ����һǧ������\n");
                  write("    �����������һ����ʮ��\n");
                  write("    ���ĵ��ж�ʮ��\n");
                  break;
         case 4:  write("    ����һǧ���������\n");
                  write("    ������ǧ����\n");
                  write("    ��������������ٵ�\n");
                  write("    ���ĵ�����ʮ��\n");
                  break;
         case 5:  write("��ķ���"+HIG+"�˺���"+NOR+"�Ѿ������������ˡ�\n");
      }
   }
   else if( fabao_ob->query("series_no") == "2"  ||
   fabao_ob->query("series_no") == "3" )  {
      dodge_stars = fabao_ob->query("stars/dodge");
      armor_stars = fabao_ob->query("stars/armor");
      force_stars = fabao_ob->query("stars/armor_vs_force");
      spells_stars = fabao_ob->query("stars/spells");
      vs_spells_stars = fabao_ob->query("stars/armor_vs_spells");
      write("�����ȼ���\n");
      write("    " + HIY+"������        "+HIR);
      for(i=0; i<dodge_stars; i++)
         write("��");
      for(i=dodge_stars; i<5; i++)
         write("��");
      write("    " + HIB+"�ֿ���        "+HIR);
      for(i=0; i<armor_stars; i++)
         write("��");
      write("\n"); 
      write("    " + HIM+"�ڹ��ֿ���    "+HIR);
      for(i=0; i<force_stars; i++)
         write("��");
      for(i=force_stars; i<5; i++)
         write("��");
      write("    " + HIC+"ħ��������    "+HIR);
      for(i=0; i<spells_stars; i++)
         write("��");
      write("\n"); 
      write("    " + HIW+"ħ���ֿ���    "+HIR);
      for(i=0; i<vs_spells_stars; i++)
         write("��");
      write(NOR+"\n"); 
      
      switch( dodge_stars )   {
         case 1:  write(HIY+"������" + NOR+ "(dodge)������Ҫ��\n");
                  write("    ��������������\n");
                  write("    ���ĵ�������\n");
                  break;
         case 2:  write(HIY+"������" + NOR+ "(dodge)������Ҫ��\n");
                  write("    �������������\n");
                  write("    ���ĵ��ж�ʮ��\n");
                  break;
         case 3:  write(HIY+"������" + NOR+ "(dodge)������Ҫ��\n");
                  write("    ����һǧ������\n");
                  write("    ���ĵ�����ʮ��\n");
                  break;
         case 4:  write(HIY+"������" + NOR+ "(dodge)������Ҫ��\n");
                  write("    ����һǧ���������\n");
                  write("    ���ĵ���һ����\n");
                  break;
         case 5:  write("��ķ���"+HIY+"������"+NOR+"�Ѿ������������ˡ�\n");
      }
      switch( armor_stars )   {
         case 1:  write(HIB+"�ֿ���" + NOR+ "(armor)������Ҫ��\n");
                  write("    ����һ��������\n");
                  write("    �����������\n");
                  write("    �������������ʮ��\n");
                  write("    ���ĵ���һ��\n");
                  break;
         case 2:  write(HIB+"�ֿ���" + NOR+ "(armor)������Ҫ��\n");
                  write("    �������������\n");
                  write("    ����һǧ����\n");
                  write("    �����������һ�ٵ�\n");
                  write("    ���ĵ�������\n");
                  break;
         case 3:  write(HIB+"�ֿ���" + NOR+ "(armor)������Ҫ��\n");
                  write("    ����һǧ������\n");
                  write("    ����һǧ������\n");
                  write("    �����������һ����ʮ��\n");
                  write("    ���ĵ��ж�ʮ��\n");
                  break;
         case 4:  write(HIB+"�ֿ���" + NOR+ "(armor)������Ҫ��\n");
                  write("    ����һǧ���������\n");
                  write("    ������ǧ����\n");
                  write("    ��������������ٵ�\n");
                  write("    ���ĵ�����ʮ��\n");
                  break;
         case 5:  write("��ķ���"+HIB+"�ֿ���"+NOR+"�Ѿ������������ˡ�\n");
      } 
      switch( force_stars )   {
         case 1:  write(HIM+"�ڹ��ֿ���" + NOR+ "(armor_vs_force)������Ҫ��\n");
                  write("    ����һ��������\n");
                  write("    �����������\n");
                  write("    �����������һ�ٵ�\n");
                  break;
         case 2:  write(HIM+"�ڹ��ֿ���" + NOR+ "(armor_vs_force)������Ҫ��\n");
                  write("    �������������\n");
                  write("    ����һǧ����\n");
                  write("    �����������һ����ʮ��\n");
                  break;
         case 3:  write(HIM+"�ڹ��ֿ���" + NOR+ "(armor_vs_force)������Ҫ��\n");
                  write("    ����һǧ������\n");
                  write("    ����һǧ������\n");
                  write("    �����������������ʮ��\n");
                  break;
         case 4:  write(HIM+"�ڹ��ֿ���" + NOR+ "(armor_vs_force)������Ҫ��\n");
                  write("    ����һǧ���������\n");
                  write("    ������ǧ����\n");
                  write("    ������������İٵ�\n");
                  break;
         case 5:  write("��ķ���"+HIM+"�ڹ��ֿ���"+NOR+"�Ѿ������������ˡ�\n");
      }
      switch( spells_stars )   {
         case 1:  write(HIC+"ħ��������" + NOR+ "(spells)������Ҫ��\n");
                  write("    ��������������\n");
                  write("    �����������\n");
                  write("    �����������ʮ��\n");
                  write("    ���ĵ�������\n");
                  break;
         case 2:  write(HIC+"ħ��������" + NOR+ "(spells)������Ҫ��\n");
                  write("    �������������\n");
                  write("    ����һǧ����\n");
                  write("    ���������һ�ٵ�\n");
                  write("    ���ĵ��ж�ʮ��\n");
                  break;
         case 3:  write(HIC+"ħ��������" + NOR+ "(spells)������Ҫ��\n");
                  write("    ����һǧ������\n");
                  write("    ����һǧ������\n");
                  write("    ���������һ����ʮ��\n");
                  write("    ���ĵ�����ʮ��\n");
                  break;
         case 4:  write(HIC+"ħ��������" + NOR+ "(spells)������Ҫ��\n");
                  write("    ����һǧ���������\n");
                  write("    ������ǧ����\n");
                  write("    ������������ٵ�\n");
                  write("    ���ĵ���һ����\n");
                  break;
         case 5:  write("��ķ���"+HIC+"ħ��������"+NOR+"�Ѿ������������ˡ�\n");
      }
      switch( vs_spells_stars )   {
         case 1:  write(HIW+"ħ���ֿ���" + NOR+ "(armor_vs_spells)������Ҫ��\n");
                  write("    ��������������\n");
                  write("    �����������\n");
                  write("    ���������һ�ٵ�\n");
                  break;
         case 2:  write(HIW+"ħ���ֿ���" + NOR+ "(armor_vs_spells)������Ҫ��\n");
                  write("    �������������\n");
                  write("    ����һǧ����\n");
                  write("    ���������һ����ʮ��\n");
                  break;
         case 3:  write(HIW+"ħ���ֿ���" + NOR+ "(armor_vs_spells)������Ҫ��\n");
                  write("    ����һǧ������\n");
                  write("    ����һǧ������\n");
                  write("    ������������ٵ�\n");
                  break;
         case 4:  write(HIW+"ħ���ֿ���" + NOR+ "(armor_vs_spells)������Ҫ��\n");
                  write("    ����һǧ���������\n");
                  write("    ������ǧ����\n");
                  write("    �����������ٵ�\n");
                  break;
         case 5:  write("��ķ���"+HIW+"ħ���ֿ���"+NOR+"�Ѿ������������ˡ�\n");
      }
   }
   
   return 1;
}

int  do_upgrade(string arg)
{
   string name, property;
   object fabao_ob, me=this_player();
   int   stars, upgraded;
  
   if( !arg || arg == "")   {
      write("���� upgrade ������ for �������� ��������\n");
      write("�������Կ��� cost ������ ���鿴��\n");
      return 1;
   }
      
   if( sscanf(arg, "%s for %s", name, property) != 2)  {
      write("���� upgrade ������ for �������� ��������\n");
      write("�������Կ��� cost ������ ���鿴��\n");
      return 1;
   }
   
   if( !objectp(fabao_ob=present(name, me)) )
      return notify_fail("������û��������������\n");
      
   if(!fabao_ob->query("owner_id") || !fabao_ob->query("series_no")) 
      return notify_fail("�Ǹ����Ƿ���Ү��\n");
     
   if( fabao_ob->query("equipped") )
      return notify_fail("�������·�������������\n");
          
   if( fabao_ob->query("series_no") == "1")  {   // weapon
      if( property != "damage" )
         return notify_fail("����û������������ԡ�\n");
      
      stars = fabao_ob->query("stars/"+property);
      upgraded = fabao_ob->query("upgraded/"+property) + 1;
      switch(stars)   {
         case 1:  if( me->query("combat_exp") < (20000+upgraded*16000) ||
                  me->query("max_force") < 500 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("weapon_prop/damage", 4);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_force", -10);
                  me->add("combat_exp", -200);
                  break;
         case 2:  if( me->query("combat_exp") < (100000+upgraded*80000) ||
                  me->query("max_force") < 1000 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("weapon_prop/damage", 6);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_force", -20);
                  me->add("combat_exp", -2000);
                  break;
         case 3:  if( me->query("combat_exp") < (500000+upgraded*100000) ||
                  me->query("max_force") < 1500 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("weapon_prop/damage", 6);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_force", -30);
                  me->add("combat_exp", -4000);
                  break;
         case 4:  if( me->query("combat_exp") < (1000000+upgraded*100000) ||
                  me->query("max_force") < 2000 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("weapon_prop/damage", 6);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_force", -40);
                  me->add("combat_exp", -10000);
                  break;
         case 5:  return notify_fail("��ķ����Ѿ������������ˡ�\n");
      }
      write(fabao_ob->query("name")+"��"+HIG+"�˺���"+NOR+"�����ˣ�\n");
   }
   else if(fabao_ob->query("series_no") == "2" ||
   fabao_ob->query("series_no") == "3")   {   // armor
      if( property != "dodge" && property != "armor" &&
      property != "armor_vs_force" && property != "spells" &&
      property != "armor_vs_spells" )
         return notify_fail("����û������������ԡ�\n");
      
      stars = fabao_ob->query("stars/"+property); 
      upgraded = fabao_ob->query("upgraded/"+property) + 1; 
      if( property == "dodge" )   {
         switch(stars)  { 
            case 1:if( me->query("combat_exp") < (20000+36000*upgraded) )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/dodge", 1);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("combat_exp", -1000);
                  break;
            case 2:if( me->query("combat_exp") < (200000+60000*upgraded) )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/dodge", 1);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("combat_exp", -4000);
                  break;
            case 3:if( me->query("combat_exp") < (500000+upgraded*100000) )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/dodge", 2);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("combat_exp", -10000);
                  break;
            case 4:if( me->query("combat_exp") < (1000000+upgraded*100000) )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/dodge", 2);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("combat_exp", -20000);
                  break;
            case 5: 
                  return notify_fail("��ķ���"+HIY+"������"+NOR+"�Ѿ������������ˡ�\n");
         }
         write(fabao_ob->query("name")+"��"+HIY+"������"+NOR+"�����ˣ�\n");
      }
      else if( property == "armor" )  {
         switch(stars)  {
            case 1: if( me->query("combat_exp") < (20000+16000*upgraded) ||
                  me->query("max_force") < 500 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/armor", 2);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_force", -10);
                  me->add("combat_exp", -200);
                  break;
            case 2: if( me->query("combat_exp") < (100000+upgraded*80000) ||
                  me->query("max_force") < 1000 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/armor", 3);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_force", -20);
                  me->add("combat_exp", -1000);
                  break;
            case 3: if( me->query("combat_exp") < (500000+upgraded*100000) ||
                  me->query("max_force") < 1500 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/armor", 4);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_force", -30);
                  me->add("combat_exp", -4000);
                  break;
            case 4: if( me->query("combat_exp") < (1000000+upgraded*100000) ||
                  me->query("max_force") < 2000 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/armor", 5);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_force", -40);
                  me->add("combat_exp", -10000);
                  break;
            case 5:  return notify_fail("��ķ���"+HIB+"�ֿ���"+NOR+"�Ѿ������������ˡ�\n");
         }
         write(fabao_ob->query("name")+"��"+HIB+"�ֿ���"+NOR+"�����ˣ�\n");
      }
      else if( property == "armor_vs_force" )  {
         switch(stars)  {
            case 1: if( me->query("combat_exp") < (20000+upgraded*16000) ||
                  me->query("max_force") < 500 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/armor_vs_force", 20);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_force", -20);
                  break;
            case 2: if( me->query("combat_exp") < (100000+upgraded*80000) ||
                  me->query("max_force") < 1000 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->set("armor_prop/armor_vs_force", 30);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_force", -30);
                  break;
            case 3: if( me->query("combat_exp") < (500000+upgraded*100000) ||
                  me->query("max_force") < 1500 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/armor_vs_force", 40);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_force", -50);
                  break;
            case 4: if( me->query("combat_exp") < (1000000+upgraded*100000) ||
                  me->query("max_force") < 2000 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/armor_vs_force", 50);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_force", -80);
                  break;
            case 5:  return notify_fail("��ķ���"+HIM+"�ڹ��ֿ���"+NOR+"�Ѿ������������ˡ�\n");
         }
         write(fabao_ob->query("name")+"��"+HIM+"�ڹ��ֿ���"+NOR+"�����ˣ�\n");
      }
      else if( property == "spells" )  {
         switch(stars)   {
            case 1: if( me->query("combat_exp") < (20000+upgraded*36000) ||
                  me->query("max_mana") < 500 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/spells", 1);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_mana", -10);
                  me->add("combat_exp", -1000);
                  break;
            case 2: if( me->query("combat_exp") < (200000+upgraded*60000) ||
                  me->query("max_mana") < 1000 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/spells", 1);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_mana", -20);
                  me->add("combat_exp", -4000);
                  break;
            case 3: if( me->query("combat_exp") < (500000+upgraded*100000) ||
                  me->query("max_mana") < 1500 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/spells", 2);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_mana", -30);
                  me->add("combat_exp", -10000);
                  break;
            case 4: if( me->query("combat_exp") < (1000000+upgraded*100000) ||
                  me->query("max_mana") < 2000 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/spells", 2);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_mana", -40);
                  me->add("combat_exp", -20000);
                  break;
            case 5:  return notify_fail("��ķ���"+HIC+"ħ��������"+NOR+"�Ѿ������������ˡ�\n");
         }
         write(fabao_ob->query("name")+"��"+HIC+"ħ��������"+NOR+"�����ˣ�\n");
      }
      else if( property == "armor_vs_spells" )  {
         switch(stars)  {
            case 1: if( me->query("combat_exp") < (20000+upgraded*36000) || 
                  me->query("max_mana") < 500 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/armor_vs_spells", 20);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_mana", -20);
                  break;
            case 2: if( me->query("combat_exp") < (20000+upgraded*80000) || 
                  me->query("max_mana") < 1000 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/armor_vs_spells", 30);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_mana", -30);
                  break;
            case 3: if( me->query("combat_exp") < (500000+upgraded*100000) || 
                  me->query("max_mana") < 1500 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/armor_vs_spells", 40);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_mana", -60);
                  break;
            case 4: if( me->query("combat_exp") < (1000000+upgraded*100000) || 
                  me->query("max_mana") < 2000 )
                     return notify_fail("������������������ cost ��ѯ��\n");
                  fabao_ob->add("armor_prop/armor_vs_spells", 50);
                  fabao_ob->add("upgraded/"+property, 1);
                  if( upgraded == 5 )  {
                     fabao_ob->add("stars/"+property, 1);
                     fabao_ob->set("upgraded/"+property, 0);
                  }
                  me->add("max_mana", -100);
                  break;
            case 5:  return notify_fail("��ķ���"+HIW+"ħ���ֿ���"+NOR+"�Ѿ������������ˡ�\n");
         }
         write(fabao_ob->query("name")+"��"+HIW+"ħ���ֿ���"+NOR+"�����ˣ�\n");
      } 
   }
  
   me->save(); 
   fabao_ob->save();
   
   return 1;
}

int  do_change_name(string arg)
{
   string name, newname;
   object fabao_ob, me=this_player();
  
   if( !arg || arg == "") 
      return notify_fail("���� change_name ���� �������� ��������\n");
      
   if( sscanf(arg, "%s %s", name, newname) != 2)
      return notify_fail("���� change_name ���� �������� ��������\n");
   
   if( !objectp(fabao_ob=present(name, me)) )
      return notify_fail("������û��������������\n");

   if(!fabao_ob->query("owner_id") || !fabao_ob->query("series_no")) 
      return notify_fail("�Ǹ����Ƿ���Ү��\n");

   if( fabao_ob->query("equipped") )
      return notify_fail("�������·������ܸ�����\n");
   
   newname += "$NOR$";      
   arg = newname;
            
        arg = replace_string(arg, "$BLK$", "");
        arg = replace_string(arg, "$RED$", "");
        arg = replace_string(arg, "$GRN$", "");
        arg = replace_string(arg, "$YEL$", "");
        arg = replace_string(arg, "$BLU$", "");
        arg = replace_string(arg, "$MAG$", "");
        arg = replace_string(arg, "$CYN$", "");
        arg = replace_string(arg, "$WHT$", "");
        arg = replace_string(arg, "$HIR$", "");
        arg = replace_string(arg, "$HIG$", "");
        arg = replace_string(arg, "$HIY$", "");
        arg = replace_string(arg, "$HIB$", "");
        arg = replace_string(arg, "$HIM$", "");
        arg = replace_string(arg, "$HIC$", "");
        arg = replace_string(arg, "$HIW$", "");
        arg = replace_string(arg, "$NOR$", "");
        
   if( !check_legal_name(arg, 12) )   {
      return 1; 
   }
  
   arg = newname;
    
        arg = replace_string(arg, "$BLK$", BLK);
        arg = replace_string(arg, "$RED$", RED);
        arg = replace_string(arg, "$GRN$", GRN);
        arg = replace_string(arg, "$YEL$", YEL);
        arg = replace_string(arg, "$BLU$", BLU);
        arg = replace_string(arg, "$MAG$", MAG);
        arg = replace_string(arg, "$CYN$", CYN);
        arg = replace_string(arg, "$WHT$", WHT);
        arg = replace_string(arg, "$HIR$", HIR);
        arg = replace_string(arg, "$HIG$", HIG);
        arg = replace_string(arg, "$HIY$", HIY);
        arg = replace_string(arg, "$HIB$", HIB);
        arg = replace_string(arg, "$HIM$", HIM);
        arg = replace_string(arg, "$HIC$", HIC);
        arg = replace_string(arg, "$HIW$", HIW);
        arg = replace_string(arg, "$NOR$", NOR);
  
   fabao_ob->set("name", arg);
   fabao_ob->save();     
   
   write("�Ķ��ɹ���\n");
   return 1;
}
      
int  do_change_id(string arg)
{
   string name, newname;
   object fabao_ob, me=this_player();
   string *id_list, *t_list;
  
   if( !arg || arg == "") 
      return notify_fail("���� change_id ���� ��Ӣ���� ��������\n");
      
   if( sscanf(arg, "%s %s", name, newname) != 2)
      return notify_fail("���� change_id ���� ��Ӣ���� ��������\n");
   
   if( !objectp(fabao_ob=present(name, me)) )
      return notify_fail("������û��������������\n");

   if(!fabao_ob->query("owner_id") || !fabao_ob->query("series_no")) 
      return notify_fail("�Ǹ����Ƿ���Ү��\n");

   if( fabao_ob->query("equipped") )
      return notify_fail("�������·������ܸ�����\n");

   if( !check_legal_id( newname ) )     return 1;
  
   newname = replace_string(newname, " ", "_"); 
   fabao_ob->set("id", newname);

   id_list = ({ newname });
   t_list = explode( newname, "_");
   if( sizeof(t_list) > 1 )   {
     id_list += t_list;
   }
   fabao_ob->set_name( fabao_ob->query("name"), id_list ); 
   fabao_ob->save();
   
   write("�Ķ��ɹ���\n");
   return 1;
}

      
int  do_change_desc(string arg)
{
   string name, newname;
   object fabao_ob, me=this_player();
  
   if( !arg || arg == "") 
      return notify_fail("���� change_desc ���� ������ ����������������\n");
      
   if( sscanf(arg, "%s %s", name, newname) != 2)
      return notify_fail("���� change_desc ���� ������ ����������������\n");
   
   if( !objectp(fabao_ob=present(name, me)) )
      return notify_fail("������û��������������\n");

   if(!fabao_ob->query("owner_id") || !fabao_ob->query("series_no")) 
      return notify_fail("�Ǹ����Ƿ���Ү��\n");

   if( fabao_ob->query("equipped") )
      return notify_fail("�������·������ܸ�����\n");

   if( !check_legal_name(newname, 60 ) )     return 1;
   
   fabao_ob->set("long", newname);
   fabao_ob->save();
   
   write("�Ķ��ɹ���\n");
   return 1;
}
      
int  do_change_unit(string arg)
{
   string name, newname;
   object fabao_ob, me=this_player();
  
   if( !arg || arg == "") 
      return notify_fail("���� change_unit ���� ��λ ��ָ��������λ��\n");
      
   if( sscanf(arg, "%s %s", name, newname) != 2)
      return notify_fail("���� change_unit ���� ��λ ��ָ��������λ��\n");
   
   if( !objectp(fabao_ob=present(name, me)) )
      return notify_fail("������û��������������\n");

   if(!fabao_ob->query("owner_id") || !fabao_ob->query("series_no")) 
      return notify_fail("�Ǹ����Ƿ���Ү��\n");

   if( fabao_ob->query("equipped") )
      return notify_fail("�������·������ܸ�����\n");

   if( !check_legal_name(newname, 2 ) )     return 1;
   
   fabao_ob->set("unit", newname);
   fabao_ob->save();
   
   write("�Ķ��ɹ���\n");
   return 1;
}



