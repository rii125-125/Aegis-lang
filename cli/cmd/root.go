/*
Copyright © 2026 rii_125-125

*/
package cmd

import (
	"fmt"
	"os"

	"github.com/spf13/cobra"

	"Aegis-lang/ver"
)


// rootCmd represents the base command when called without any subcommands
var rootCmd = &cobra.Command{
	Use:   "aegis",
	Short: "Hello Aegis-lang.",
	Long: `Aegis-lang is,
> A language that makes type safety and robust code more intuitive and easier to understand.`,
	Run: func(cmd *cobra.Command, args []string) {
    	fmt.Println("Hello! Aegis!\n-------------")
		fmt.Println(ver.Ver)
	},
}

// Execute adds all child commands to the root command and sets flags appropriately.
// This is called by main.main(). It only needs to happen once to the rootCmd.
func Execute() {
	err := rootCmd.Execute()
	if err != nil {
		os.Exit(1)
	}
}

func init() {
	rootCmd.Flags().BoolP("toggle", "t", false, "Help message for toggle")
}


