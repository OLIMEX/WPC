(defproject convert "1.0.0a"
  :description "Expression converter"
  :aot [expr.CustomVisitor convert.core]
  :main convert.core
  :dependencies [[org.clojure/clojure "1.4.0"]
                 [org.clojure/tools.trace "0.7.3"]
                 [org.antlr/antlr "4.0"]]
  :java-source-paths ["java"]
)
