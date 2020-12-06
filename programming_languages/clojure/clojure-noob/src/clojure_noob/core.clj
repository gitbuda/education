;; https://www.braveclojure.com/do-things/

;; https://clojure.org/guides/weird_characters

(use 'clojure.repl)

(ns clojure-noob.core
  (:gen-class))

(defn error-message
  [severity]
  (str "OH GOD "
       (if (= severity :mild)
         "Mild"
         "Fatal")))
(error-message :mild)

;; https://clojure.org/guides/threading_macros
(-> "1" (str "2") (str "3")) ;; 123
(->> "1" (str "2") (str "3")) ;; 321

{}

(= "0" "0")
(if true true false)
(do (if () true false))

(def data-map (hash-map :a 1 :b 2))
(println (get data-map :a))

(println (:a {:a 1 :b 2}))

(conj [1 2 3] 4)

'(1 2 3 4)

#{"one" 2 3}

(contains? (set [3 3 3 4 4]) 2)

((or + -) 1 2 3)

(defn custom-inc
  "Custom increment method"
  [x]
  (+ x 1))
(map custom-inc [1 2])

(defn weird-arity
  ([] "test")
  ([number] (inc number)))
(weird-arity)
(weird-arity 1)

(defn favorite-things
  [name & things]
  (str "Hi " name " things " (clojure.string/join ", " things)))
(favorite-things "buda" "vim" "plugins")

;; Destructuring
(defn location
  ;;[{lat :lat lng :lng}]
  [{:keys [lat lng]}]
  (println (str "Lat: " lat))
  (println (str "Lng: " lng)))
(location {:lat 10 :lng 20})

;; Anonymous Functions
(map (fn [n] (inc n)) [1 2 3])
(map #(str "Hi " %) ["John" "Bill"])
(map #(str "Hi " %1) ["John" "Bill"])

(defn inc-maker
  "Craete a custom incrementor"
  [inc-by]
  #(+ % inc-by))
(def inc3 (inc-maker 3))
(inc3 7)

(let [x 3] x)
(def x 0)
(def x (inc x))
(println x)

(loop [iteration 0]
  (println (str "Iteraton " iteration))
  (if (> iteration 3)
    (println "goodbye")
    (recur (inc iteration))))

;; TODO: Pulling It All Together

(defn -main
  "I don't do a whole lot ... yet."
  [& args]
  (println (first args))
  (def var-test "bla")
  (println var-test)
  (and true true)
  (or (= 0 1) (= "yes" "no"))
  (if (nil? nil)
    (do (println "true") (println "still in do"))
    (println "false"))
  (when (= 1 1)
    (println "in when")
    (println "still in when"))
  (println (str "1" "2"))
  (println "Hello, World!"))
