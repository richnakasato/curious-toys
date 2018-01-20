/*
 * Discussion with fellow engineer about adding elements to a map of maps.
 * Explores two concepts:
 *
 *  1) What happens when we need to add a new node to the child map if the
 *  parent doesn't exist?  I expect we'll need to add the parent map node first,
 *  then add the child node.  I suspect we cannot do both at the same time.
 *  *edit: Wrong!  We can just index and go!
 *  *reference: https://stackoverflow.com/questions/10124679/what-happens-if-i-read-a-maps-value-where-the-key-does-not-exist
 *
 *  2) I assert that if we have an if block that checks for the parent node
 *  first, then the child node, we can always add the child node after checking
 *  for and resolving the first part of this conditional (does parent exist).
 *  *edit: Feels like this is OBE considering #1
 *
 */

#include <iostream>
#include <map>

#include <cassert>

int main() {
  std::map<std::string, std::map<std::string, std::string> > parents;

  // test concept 1 - can we add parent and child at the same time?
  parents["parent_1"]["child_1"] = "val_1";
  assert(parents["parent_1"]["child_1"] == "val_1"); // works!

  // I assumed we would have to do the following:
  std::map<std::string, std::string> children_of_parent_1;
  children_of_parent_1.insert(std::make_pair("child_1", "val_1"));
  parents.insert(std::make_pair("parent_1", children_of_parent_1));
  assert(parents["parent_1"]["child_1"] == "val_1"); // expected to work

  // test concept 2 - what's the best way to handle adding child_x == val_x if
  // we aren't sure the parent of child exist?

  // test that the parent doesn't exist and just add parent and child at once
  if (parents.find("parent_2") == parents.end() ||
      parents["parent_2"].find("child_1") == parents["parent_2"].end()) {
    parents["parent_2"]["child_1"] = "val_1";
    assert(parents["parent_2"]["child_1"] == "val_1"); // works!
  }
  parents["parent_2"]["child_1"] = "new_val_1";
  assert(parents["parent_2"]["child_1"] != "val_1");
  assert(parents["parent_2"]["child_1"] == "new_val_1");

  // what happens if parent exists?
  if (parents.find("parent_2") == parents.end() ||
      parents["parent_2"].find("child_2") == parents["parent_2"].end()) {
    parents["parent_2"]["child_2"] = "val_2";
    assert(parents["parent_2"]["child_2"] == "val_2"); // still works!
  }

  // can't we just do this? i.e. - parent 3 doesn't exist, so make it, and set
  // child 1 of that parent to val - YEP!
  parents["parent_3"]["child_1"] = "val_1";
  assert(parents["parent_3"]["child_1"] == "val_1");

  return 0;
}
