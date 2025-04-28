#ifndef DB_HELPER_H
#define DB_HELPER_H

#include "includes.h"

class DB_Helper
{
public:
  static bool is_username_in_DB(const std::string &username);
  static void create_new_profile_in_DB(const std::string &username);
  static void update_profile_in_DB(const Player_Data &new_data);
  static Player_Data get_profile_from_username_in_DB(const std::string &username);
  static std::vector<std::string> get_all_profiles_in_DB();

private:
  static int count_callback(void *value, int argc, char **argv, char **column_names);
  static int player_data_callback(void *value, int argc, char **argv, char **column_names);
  static int string_vector_callback(void *value, int argc, char **argv, char **column_names);
};

#endif
